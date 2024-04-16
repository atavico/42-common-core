import { Injectable, OnDestroy, OnInit } from '@angular/core';
import { webSocket, WebSocketSubject } from 'rxjs/webSocket';
import { Global, Partecipant, RefreshGame, structure } from '../shared/global';
import { AuthService } from './auth.service';
import { takeUntil, Observable, Subject } from 'rxjs';
import { Router, NavigationStart} from '@angular/router';
import { getWsUrl } from '../shared/generic';

@Injectable({
  providedIn: 'root',
})
export class WebsocketService {
  private onlineFriendSocket$: WebSocketSubject<any> = webSocket('');
  private onlineFriendLogout$ = new Subject<void>();
  private url = getWsUrl() + '/ws/active_users/';

  private tournamentSocket$: WebSocketSubject<any> = webSocket('');
  private tournamentLogout$ = new Subject<void>();
  private tournamentUrl = getWsUrl() + '/ws/tournaments/';
  private sockActive: boolean;

  sub:any;
  constructor(
    private global: Global,
    private authService: AuthService,
    private router: Router,
  ) {
      this.sockActive = false;
      //console.log("constructor");
      this.router.events
        .subscribe((event: any) => {
            if (event == undefined) {
              return ;
            };
            if (event instanceof NavigationStart) {
                // Show loading indicator
              //console.log("Done -> ", event.url);
              let good = ["/queue", "/match", "/tournament-pre", "/tournament"];
              let found:boolean = false;
              for (let i of good){
                if (i == event.url){
                  found = true;
                  break ;
                }
              }
              if (! found){                
                //console.log("Socket should close if open");
                this.resetTournamentSocket();
                this.global.matchPartecipants.next([]);
                //console.log("matchP: ", this.global.matchPartecipants);
              }
            };
          },
          (error) => {
            //console.log("What do you want");
          }
          );
    }

  i = 0;
  reinitializeOnlineFriendSocket(): void {
    this.onlineFriendLogout$.next();
    this.initializeOnlineFriendSocket();
    ////console.log("websocketToken",localStorage.getItem('token'));
  }

  private initializeOnlineFriendSocket(): void {
    this.sub = this.onlineFriendSocket$ = webSocket({
      url: this.url + '?tok=' + localStorage.getItem('token'),
      deserializer: (msg) => JSON.parse(msg.data),
      serializer: (msg) => JSON.stringify(msg),
    });

    this.onlineFriendSocket$
      .pipe(takeUntil(this.onlineFriendLogout$))
      .subscribe({
        next: (data) => {
          // //console.log('Data from onlineFriendSocket$: ', data);
          if (data.action === 'already_logged'){
            localStorage.removeItem('token');
            this.router.navigate(['alredy-logged-in']);
          }
        },
        error: (err) => {
          //console.error('Error from onlineFriendSocket$: ', err);
        },
        complete: () => {
          //console.log('WebSocket connection closed');
        },
      });
  }

  initializeTournamentSocket(matchId: number, password: string, obs: boolean): Observable<any> {
    // Set up the WebSocket connection with the provided matchId

    let queryset = "?";
    queryset += ("tok=" + localStorage.getItem('token'));
    // if (password !== '')
    //   queryset = queryset + ("&pwd=" + password);
    if (obs === true)
      queryset = queryset + ("&observer=" + obs);

    //console.log("Tournament socket queryset: ", queryset);

    this.tournamentSocket$ = webSocket({
      url: this.tournamentUrl + matchId + queryset,
      deserializer: (msg) => JSON.parse(msg.data),
      serializer: (msg) => JSON.stringify(msg),
    });
    //error handling
    this.tournamentSocket$.subscribe({
      next: (data) => {
        if (data.action !== 'game_refresh')
          //console.log('Data from tournamentSocket$: ', data);
        
        if(data.action === 'users_connected') {
          for (let key in data.players_list) {
            let partecipant: Partecipant = { id: data.players_list[key].id, nick: data.players_list[key].username, ready: data.players_list[key].ready, avatar: data.players_list[key].avatar };
            //console.log('users_connected_partecipant', partecipant);
            let currentPartecipants = this.global.matchPartecipants.getValue();
            //console.log('users_connectedCuuuuuurrent', currentPartecipants);
            currentPartecipants.push(partecipant);
            //console.log('user_connPush', currentPartecipants);
            this.global.matchPartecipants.next(currentPartecipants);
          }
        }
        else if(data.action === 'tournament_end') {
          this.router.navigate(["/end-game"]);
        }
        else if (data.action === 'new_connection') {
          let partecipant: Partecipant = { id: data.id, nick: data.username, ready: false, avatar: data.avatar};
          let currentPartecipants = this.global.matchPartecipants.getValue();
          currentPartecipants.push(partecipant);
          this.global.matchPartecipants.next(currentPartecipants);
        }
        else if (data.action === 'user_disconnection') {
          //console.log('user_disconnection', data);
        }
        else if (data.action === 'queue_user_disconnection') {
          let IdToDelete = data.id;
          let currentPartecipants = this.global.matchPartecipants.getValue();
          currentPartecipants = currentPartecipants.filter(partecipant => partecipant.id !== IdToDelete);
          this.global.matchPartecipants.next(currentPartecipants);

        }
        else if(data.action === 'to_tournament') {
          this.global.isTournament = true;
          let struct: structure = {} as structure;
          //console.log("to_tournament full: ", data);
          //console.log('to_tournament', data.tournament.structure.semifinals);
          
          this.global.turn = '';
          this.global.turn = data.tournament.turn;
          //da rivedere
          if (data.tournament.structure.turn === 'finals') {
            this.global.finalWinner[0] = data.tournament.winners.finals[0];
            this.global.finalWinner[1] = data.tournament.winners.finals[1];
          }
          this.global.finals = [];
          for (let i = 0; i < data.tournament.structure.finals.length; i++) {
            for (let j = 0; j < data.tournament.structure.finals[i].length; j++) {
              this.global.finals.push(data.tournament.structure.finals[i][j]);
            }
          }
          this.global.semifinals = [];
          for (let i = 0; i < data.tournament.structure.semifinals.length; i++) {
            for (let j = 0; j < data.tournament.structure.semifinals[i].length; j++) {
              this.global.semifinals.push(data.tournament.structure.semifinals[i][j]);
            }
          }
          this.global.quarter = [];
          for (let i = 0; i < data.tournament.structure.quarters.length; i++) {
            for (let j = 0; j < data.tournament.structure.quarters[i].length; j++) {
              this.global.quarter.push(data.tournament.structure.quarters[i][j]);
            }
          }
          this.global.quarterWinner = [];
          for (let i = 0; i < data.tournament.winners.quarters.length; i++) {
            this.global.quarterWinner.push(data.tournament.winners.quarters[i]);
          }
          this.global.semiWinner = [];
          for (let i = 0; i < data.tournament.winners.semifinals.length; i++) {
            this.global.semiWinner.push(data.tournament.winners.semifinals[i]);
          }
          this.global.finalWinner = [];
          for (let i = 0; i < data.tournament.winners.finals.length; i++) {
            this.global.finalWinner.push(data.tournament.winners.finals[i]);
          }

          this.global.placements = [];
          for (let i = 0; i < data.tournament.placements.length; i++) {
            this.global.placements.push(data.tournament.placements[i]);
          }

          //console.log('Before blockchain parsing');
          if(data.tx_hash !== undefined && data.tx_hash !== null) {
            this.global.hash_tx = data.tx_hash;
          }
          
          this.global.nextMatch = data.tournament.next_match;
          this.router.navigate(["/tournament-pre"]);
          // if (data.tournament.status === 'finished') {
          //   this.global.isTournament = false;
          // }
        }
        else if(data.action === 'to_game') {
          this.global.IdPartecipants = [];
          this.global.IdPartecipants.push(data.player_1);
          this.global.IdPartecipants.push(data.player_2); 
          //console.log('to_game PLAYERS', data.player_1, data.player_2);
          this.router.navigate(["/match"]);
        }
        else if (data.action === 'user_tournament_ready') {
          //console.log('Data from tournamentSocket$: ', data);
          let participant = this.global.matchPartecipants.getValue().find((participant: Partecipant) => participant.id === data.id);
          if (participant) {
            participant.ready = data.ready;
          }
        }
        else if (data.action === 'game_end') {
          //console.log('Data from tournamentSocket$: ', data);
          this.global.finalWinner[1] = data.winner;
          this.router.navigate(["/end-game"]);
          this.resetTournamentSocket();
        }
        else if (data.action === 'to_main_menu')
        {
          this.router.navigate(["/main-menu"])
        }
        else if (data.action === 'to_lobby')
        {
          alert("Match were full!");
          this.router.navigate(["/lobby"]);
        }
        else if (data.action === 'user_game_ready') {
          this.global.userGameReady.id = data.id;
          this.global.userGameReady.ready = data.ready;
        }
      },
      error: (err) => {
        //console.error('Error from tournamentSocket$: ', err);
      },
      complete: () => {
        //console.log('websocket connection closed');
      }
    });
    this.sockActive = true;
    return this.tournamentSocket$.asObservable();
  }

  getTournamentSocket(): Observable<any> {
    return this.tournamentSocket$.asObservable();
  }

  readyToPlay(id: number, ready: boolean) {
    return this.tournamentSocket$.next({
      action: 'tournament_ready',
      id: id,
      ready: ready
    });
  }

  readyToPlayMatch(id: number, ready: boolean) {
    return this.tournamentSocket$.next({
      action: 'game_ready',
      id: id,
      ready: ready
    });
  }

  key_event(key: any, pressed: boolean) {
    // //console.log("key event socket: ", key, pressed);
    this.tournamentSocket$.next({
      action: "key_event",
      key: key,
      pressed: pressed,
    });
  }

  settingUpdate(action: string, name: string, id: number): void {
    this.onlineFriendSocket$.next({
      action: action,
      name: name,
      id: id,
    });
  }

  sendFriendDeleted(id: number): void {
    //console.log('Friend deleted: ', id);
    this.onlineFriendSocket$.next({
      action: 'friend_deleted',
      friend_id: id,
    });
  }

  sendFriendAccepted(id: number): void {
    this.onlineFriendSocket$.next({
      action: 'friend_added',
      friend_id: id,
    });
  }

  sendFriendRequest(id: number): void {
    this.onlineFriendSocket$.next({
      action: 'new_friend_request',
      friend_id: id,
    });
  }

  endGame(): Observable<any> {
    return this.tournamentSocket$.asObservable();
  }

  closeWebSocket() {
    this.onlineFriendLogout$.next();
    this.onlineFriendLogout$.complete();
    // Reinitialize the logout subject for future logins
    this.onlineFriendLogout$ = new Subject();
  }

  closeActiveUsersWebSocket(): void {
    this.onlineFriendLogout$.next();
    this.onlineFriendLogout$.complete();
    this.sub.unsubscribe();
  }

  closeTournamentWebSocket(): void {
    this.tournamentLogout$.next();
    this.tournamentLogout$.complete();
    this.sub.unsubscribe();
  }

  resetTournamentSocket(): void {
    if (this.tournamentSocket$ && this.sockActive) {
      this.tournamentLogout$.next();
      this.tournamentSocket$.complete();
      this.tournamentSocket$.unsubscribe();
      //console.log("Socket closed");
      this.sockActive = false;
    }
  }

  getActiveUsers(): Observable<any> {
    return this.onlineFriendSocket$.asObservable();
  }

  getRefreshGame(): Observable<any> {
    return this.tournamentSocket$.asObservable();
  }

  matchEvent(event: any) {
    return this.tournamentSocket$.next(event);
  }

}

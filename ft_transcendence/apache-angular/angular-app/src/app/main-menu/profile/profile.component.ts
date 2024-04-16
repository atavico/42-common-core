// angular imports
import { Component } from '@angular/core';
import { HttpErrorResponse } from '@angular/common/http';
import { catchError } from 'rxjs/operators';
import { throwError, Observable, pipe } from 'rxjs';
// service
import { FriendService } from 'src/app/service/friend.service';
import { LanguageService } from 'src/app/service/language.service';
import { AudioService } from 'src/app/service/audio.service';
import { UpdateService } from 'src/app/service/update.service';
import { WebsocketService } from 'src/app/service/websocket.service';
import { GameService } from 'src/app/service/game.service';
// other
import { SidePanelComponent } from '../side-panel/side-panel.component';
import { Global } from 'src/app/shared/global';

@Component({
  selector: 'app-profile',
  templateUrl: './profile.component.html',
  styleUrls: ['./profile.component.css'],
})
export class ProfileComponent {
  //HTML variables
  statistics: string = 'Statistics';
  victorys: string = 'Victories';
  victory: string = 'Victory';
  defeats: string = 'Defeats';
  defeat: string = 'Defeat';
  deleteFriend: string = 'Delete friend';
  back: string = 'Back';
  addFriend: string = 'Add friend';
  decline: string = 'Decline';
  gamesPlayed: string = 'Games played';
  serverErrorText: string = 'Server error';
  noGamesPlayed: string = 'No games played :(';
  tournamentParticipated: string = 'Tournaments Participated';
  firstPlaceStr: string = 'First Places';
  secondPlaceStr: string = 'Second Places';
  thirdPlaceStr: string = 'Third Places';
  tournament: string = 'Tournament';
  isOnline: boolean = true;
  singleTournament: number = 0;

  //User variables
  profilePic = '';
  nickName: string = '';
  idNick: string = '';
  language = this.global.user.getLanguage() ?? 'en';
  gamesWon: number = 0;
  gamesLost: number = 0;
  tParticipated: number = 0;
  tFirstPlace: number = 0;
  tSecondPlace: number = 0;
  tThirdPlace: number = 0;
  games1: {
    date: string;
    won: boolean;
    versus: string;
    score: string;
    type: string;
  }[] = [];
  gamesT: {
    date: string;
    placement: string;
    winnerNick: string;
    playerCount: number;
    won: boolean;
  }[] = [];
  gamesL1: {
    date: string;
    won: boolean;
    versus: string;
    score: string;
    type: string;
  }[] = [];
  gamesLT: {
    date: string;
    winnerNick: string;
    secondNick: string;
    playerCount: number;
    won: boolean;
  }[] = [];

  constructor(
    private languageService: LanguageService,
    private sidePanelComponent: SidePanelComponent,
    private global: Global,
    private friendService: FriendService,
    private audioService: AudioService,
    private updateService: UpdateService,
    private websocketService: WebsocketService,
    private gameService: GameService
  ) {}

  isFriend: boolean = false;
  isFriendReq: boolean = false;
  ngOnInit(): void {
    this.updateLocalizedStrings();
    if (this.sidePanelComponent.isUser == true) {
      this.takeUserFromProfile(this.global.user.getId());
    } else {
      this.takeUserFromProfile(Number(this.sidePanelComponent.userProfile));
    }
    if (this.sidePanelComponent.isFriend == true) this.isFriend = true;
    else if (this.sidePanelComponent.isFriendReq == true)
      this.isFriendReq = true;
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[this.global.user.getLanguage() ?? 'en'];
      const keysToUpdate = [
        'statistics',
        'victorys',
        'victory',
        'defeats',
        'defeat',
        'deleteFriend',
        'back',
        'addFriend',
        'decline',
        'gamesPlayed',
        'serverErrorText',
        'noGamesPlayed',
        'tournamentParticipated',
        'firstPlaceStr',
        'secondPlaceStr',
        'thirdPlaceStr',
        'tournament',
      ];
      for (let key of keysToUpdate) {
        if (langData.hasOwnProperty(key)) {
          this[key] = langData[key];
        }
      }
    });
  }

  isOnlineUser(id: string) {
    if ((this.global.onlineUsers as any).active_users.includes(Number(id))) {
      return true;
    }
    return false;
  }

  takeUserFromProfile(id: number) {
    this.isOnline = this.isOnlineUser(id.toString());

    this.takeUserInfo(id);
    this.takeGamesPlayed1v1(id);
    this.takeGamesPlayedTournament(id);
    this.takeGamesLocal1v1(id);
    this.takeGamesLocalTournament(id);
  }

  takeUserInfo(id: number) {
    this.friendService.getUserID(id).subscribe((data) => {
      this.profilePic = data.data.avatar;
      this.nickName = data.data.username;
      this.idNick = data.data.player_id;
      this.gamesWon = data.data.games_won;
      this.gamesLost = data.data.games_lost;
      this.tParticipated = data.data.tournaments_played;

      let placements = JSON.parse(data.data.tournaments_placements);

      this.tFirstPlace = placements[0];
      this.tSecondPlace = placements[1];
      this.tThirdPlace = placements[2];
    });
  }

  takeGamesPlayed1v1(id: number) {
    this.friendService.getGamesPlayed1(id)?.subscribe((data) => {
      let lenGames = data.data.games.length;
      for (let i = 0; i < lenGames; i++) {
        let date = new Date(data.data.games[i].date);
        let formattedDate = date.toISOString().split('T')[0];
        let versusId =
          data.data.games[i].won_by == id
            ? data.data.games[i].lost_by
            : data.data.games[i].won_by;
        let versusNick = this.global.userMap.get(versusId.toString())
          ? this.global.userMap.get(versusId.toString()) + '#' + versusId
          : 'unknown#' + versusId;
        let matchType =
          data.data.games[i].tournament_game == true ? 'Tournament' : '1v1';

        let game = {
          date: formattedDate,
          won: data.data.games[i].won_by == id,
          versus: versusNick,
          score:
            data.data.games[i].player1_score +
            ' - ' +
            data.data.games[i].player2_score,
          type: matchType,
        };
        this.games1.push(game);
      }
    });
  }

  takeGamesLocal1v1(id: number) {
    this.gameService.getLocalMatches(id)?.subscribe((data: any) => {
      let lenGames = data.data.games.length;
      for (let i = 0; i < lenGames; i++) {
        let date = new Date(data.data.games[i].date);
        let formattedDate = date.toISOString().split('T')[0];
        let versusNick;
        if (data.data.games[i].winner == data.data.games[i].username) {
          if (data.data.games[i].player1 == data.data.games[i].winner)
            versusNick = data.data.games[i].player2;
          else versusNick = data.data.games[i].player1;
        } else {
          versusNick = data.data.games[i].winner;
        }
        let wonBool: boolean =
          data.data.games[i].winner == data.data.games[i].username;
        let game = {
          date: formattedDate,
          won: wonBool,
          versus: versusNick,
          score:
            data.data.games[i].p1_score + ' - ' + data.data.games[i].p2_score,
          type: 'Local 1v1',
        };
        this.gamesL1.push(game);
      }
    });
  }

  takeGamesLocalTournament(id: number) {
    // this.gameService.getLocalTournaments(id).subscribe((data) => {
    //   let lenGames = data.data.games.length;
    //   for (let i = 0; i < lenGames; i++) {
    //     let date = new Date(data.data.games[i].date);
    //     let formattedDate = date.toISOString().split('T')[0];
    //     let game = {
    //       date: formattedDate,
    //       winnerNick: data.data.games[i].winner,
    //       secondNick: data.data.games[i].second,
    //       playerCount: data.data.games[i].players.length,
    //       won: data.data.games[i].winner == id,
    //     };
    //   }
    // });
  }

  takeGamesPlayedTournament(id: number) {
    this.friendService.getGamesPlayedT(id).subscribe((data) => {
      let lenGames = data.data.tournaments.length;
      for (let i = 0; i < lenGames; i++) {
        let date = new Date(data.data.tournaments[i].end_timestamp);
        let formattedDate = date.toISOString().split('T')[0];
        let placements = JSON.parse(data.data.tournaments[i].placements);
        let placement = 1;
        let firstPlaceId =
          placements[0] == this.global.user.getId() ? true : false;
        for (let j = 0; j < placements.length; j++) {
          if (placements[j] == id) {
            placement = j + 1;
            break;
          }
        }

        let winnerUsername = this.global.userMap.get(placements[0].toString())
          ? this.global.userMap.get(placements[0].toString()) +
            '#' +
            placements[0]
          : 'unknown#';

        let game = {
          date: formattedDate,
          placement: 'Place ' + placement + '*',
          winnerNick: winnerUsername,
          playerCount: Number(data.data.tournaments[i].max_partecipants),
          won: firstPlaceId,
        };
        this.gamesT.push(game);
      }
    });
  }

  clickDelete() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.friendService.deleteFriend(Number(this.idNick)).subscribe(() => {
      this.websocketService.sendFriendDeleted(Number(this.idNick));
      this.updateService.triggerUpdate();
    });
    this.closeProfile();
  }

  serverError: boolean = false;
  clickStatus(status: string) {
    this.audioService.playAudio(this.audioService.clickButton);

    this.serverError = false;
    let creator = this.sidePanelComponent.userProfile;
    let receiver = this.global.user.getId();
    this.friendService
      .friendStatus(Number(creator), receiver, status)
      .pipe(
        catchError((error: HttpErrorResponse) => {
          this.serverError = true;
          return throwError(() => error);
        })
      )
      .subscribe((data) => {
        if (status == 'accepted') {
          this.websocketService.sendFriendAccepted(Number(creator));
          this.global.user.cleanFriendList();
          let friendList = JSON.parse(data.data.friend_list);
          friendList.forEach((element: any) => {
            this.global.user.addFriend(element);
          });
        }
        this.updateService.triggerUpdate();
        this.closeProfile();
      });
  }

  closeProfile() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.sidePanelComponent.isUser = false;
    this.sidePanelComponent.isProfileOpen = false;
    this.sidePanelComponent.isFriend = false;
    this.sidePanelComponent.isFriendReq = false;
  }
}

import { Component, OnDestroy, OnInit } from '@angular/core';
import { NavigationEnd, Router } from '@angular/router';
import { AudioService } from 'src/app/service/audio.service';
import { GameService } from 'src/app/service/game.service';
import { Match } from './match.model';
import { WebsocketService } from 'src/app/service/websocket.service';
import { Global } from 'src/app/shared/global';
import { LanguageService } from 'src/app/service/language.service';
import { Partecipant } from 'src/app/shared/global';

@Component({
  selector: 'app-lobby',
  templateUrl: './lobby.component.html',
  styleUrls: ['./lobby.component.css'],
})
export class LobbyComponent implements OnInit, OnDestroy {
  oneVoneMatches: Match[] = [];
  tournamentMatches: Match[] = [];
  watchMatches: Match[] = [];
  showWatchMatch: boolean = false;

  // HTML variables
  refreshStr: string = 'Refresh';
  creator: string = 'Creator';
  score: string = 'Score';
  slots: string = 'Slots';
  join: string = 'Join';
  watch: string = 'Watch';
  tournament: string = 'Tournament';
  watchMatchStr: string = 'Watch Match';
  back: string = 'Back';
  hostMatchStr: string = 'Host Match';

  constructor(
    private router: Router,
    private audioService: AudioService,
    private gameService: GameService,
    private webSocketService: WebsocketService,
    private global: Global,
    private languageService: LanguageService
  ) {}

  ngOnInit() {
    this.refresh();
    this.updateLocalizedStrings();
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[localStorage.getItem('language') || 'en'];
      const keysToUpdate = [
        'refreshStr',
        'creator',
        'score',
        'slots',
        'join',
        'watch',
        'tournament',
        'watchMatchStr',
        'back',
        'hostMatchStr',
      ];
      for (let key of keysToUpdate) {
        if (langData.hasOwnProperty(key)) {
          this[key] = langData[key];
        }
      }
    });
  }

  ngOnDestroy() {
    //this.webSocketService.closeTournamentWebSocket();
  }

  removeCurrentUserFromPartecipants(): void {
    const currentUserId = this.global.user.getId();
    const currentPartecipants = this.global.matchPartecipants.getValue();
    const filteredPartecipants = currentPartecipants.filter((partecipant: Partecipant) => partecipant.id !== currentUserId);
    this.global.matchPartecipants.next(filteredPartecipants);
    //console.log("CleanPartecipants", filteredPartecipants);
}

  gameOptions = false;

  joinToMatch(match: Match) {
    //console.log('MatchProvaJOIN: ', match);
    this.audioService.playAudio(this.audioService.clickButton);
    // controllare password
    if (match.password === true) {
      let password = prompt('Enter the password');
      //console.log('password: ', password);
      // todo: mandare password al server e controllare se corretta
    }

    // controllare se ancora attivo
    this.gameService.getMatches().subscribe((data: any) => {
      let mat = data.data.filter((m: any) => m.id === match.id)[0];
      if (mat.status === 'pending' &&
          match.players_id.split(',').length < match.max_partecipants) {
        this.webSocketService.initializeTournamentSocket(match.id, '', false);
        this.global.tournamentID = match.id;
        this.global.currentGame = match;
        this.router.navigate(['/queue']);
      } else {
        // //console.log(mat);
        alert('Match is no longer available');
      }
    });
  }

  watchMatch(match: Match) {
    this.audioService.playAudio(this.audioService.clickButton);
    // controllare che il match esista ancora
    this.gameService.getMatches().subscribe((data: any) => {
      let mat = data.data.filter((m: any) => m.id === match.id)[0];
      if (mat.status === 'started') {
        console.log("match id: ", match.id);
        this.webSocketService.initializeTournamentSocket(match.id, '', true);
        //? andare al match?
        // this.router.navigate(['/match']);
      } else {
        alert('Match is no longer available, please refresh the page');
      }
    });

    // this.webSocketService.initializeTournamentSocket(match.id, '', true);
    //todo: implement watch match
  }

  refresh() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.gameService.getMatches().subscribe((data: any) => {
      // //console.log('matches: ', data.data);
      if (data.data === undefined) {
        return;
      }
      this.oneVoneMatches = data.data.filter(
        (match: any) =>
          match.game_type === '1 vs 1' &&
          match.status === 'pending' &&
          match.players_id.split(',').length < match.max_partecipants &&
          this.checkIfPlayerIsfriend(match) === true
        // match.started === 'false'
      );
      this.tournamentMatches = data.data.filter(
        (match: any) =>
          match.game_type === 'Tournament' &&
          match.status === 'pending' &&
          match.players_id.split(',').length < match.max_partecipants &&
          this.checkIfPlayerIsfriend(match) === true
        // match.started === 'false'
      );
      let oneVoneWatch: Match[] = [];
      let tournamentWatch: Match[] = [];
      for (let match of data.data) {
        if (match.status === 'started') {
          if (match.game_type === '1 vs 1') {
            oneVoneWatch.push(match);
          } else {
            tournamentWatch.push(match);
          }
        }
      }
      this.watchMatches = oneVoneWatch.concat(tournamentWatch);
      //console.log('1v1: ', this.oneVoneMatches);
      //console.log('tournament: ', this.tournamentMatches);
    });
  }

  checkIfPlayerIsfriend(match: Match) {
    if (match.friends_only === true) {
      if (this.global.user.getFriendList().includes(Number(match.creator))) {
        return true;
      } else return false;
    }
    return true;
  }

  getCreator(creator: number) {
    return this.global.userMap.get(creator.toString());
  }

  getHowManyPlayers(players: string) {
    return players.split(',').length;
  }

  changePlayWatch() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.showWatchMatch = !this.showWatchMatch;
  }

  backCall() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.router.navigate(['/main-menu']);
  }

  hostMatch() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.router.navigate(['/host-menu']);
  }
}

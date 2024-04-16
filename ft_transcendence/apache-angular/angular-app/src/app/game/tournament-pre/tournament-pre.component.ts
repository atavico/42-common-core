import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Global } from 'src/app/shared/global';
import { user } from 'src/app/game/tournament-pre/user.model';
import { WebsocketService } from 'src/app/service/websocket.service';
import { LanguageService } from 'src/app/service/language.service';

@Component({
  selector: 'app-tournament-pre',
  templateUrl: './tournament-pre.component.html',
  styleUrls: ['./tournament-pre.component.css'],
})
export class TournamentPreComponent implements OnInit {
  // HTML variables
  finalsStr: string = 'Finals';
  firstSecondPlaceStr: string = 'First and Second places';
  thirdFourthPlaceStr: string = 'Third and Fourth places';
  notMyTurn: string = 'Not my turn';
  semiFinalsStr: string = 'Semifinals';
  quartersStr: string = 'Quarters';

  constructor(
    private router: Router,
    private global: Global,
    private websocket: WebsocketService,
    private languageService: LanguageService
  ) {}

  quarterArray: string[][] = [
    ['1', '2'],
    ['3', '4'],
    ['5', '6'],
    ['7', '8'],
  ];
  semiArray: string[][] = [
    ['1', '2'],
    ['3', '4'],
  ];
  finalArray: string[][] = [
    ['1', '2'],
    ['3', '4'],
  ];

  quarterWinner: string[] = ['', '', '', ''];
  semiWinner: string[] = ['', ''];
  finalWinner: string[] = ['', ''];

  turn: string = '';
  userReady: {
    id: number;
    ready: boolean;
  } = { id: -1, ready: false };

  usersQuarter: user[] = [];
  usersSemi: user[] = [];
  usersFinal: user[] = [];

  next_Match: string =
    this.global.nextMatch[0] + ' vs ' + this.global.nextMatch[1];

  ngOnInit() {
    this.updateLocalizedStrings();

    this.quarterArray = this.global.quarter;
    this.semiArray = this.global.semifinals;
    this.finalArray = this.global.finals;

    this.quarterWinner = this.global.quarterWinner;
    this.semiWinner = this.global.semiWinner;
    this.finalWinner = this.global.finalWinner;

    this.turn = this.global.turn;

    this.getPlayer();

    this.global.usersQuarter = this.usersQuarter;
    this.global.usersSemi = this.usersSemi;
    this.global.usersFinal = this.usersFinal;

    this.userReady = this.global.userGameReady;
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[this.global.user.getLanguage() ?? 'en'];
      const keysToUpdate = [
        'finalsStr',
        'firstSecondPlaceStr',
        'thirdFourthPlaceStr',
        'notMyTurn',
        'semiFinalsStr',
        'quartersStr',
      ];
      for (let key of keysToUpdate) {
        if (langData.hasOwnProperty(key)) {
          this[key] = langData[key];
        }
      }
    });
  }

  allValuesNull(): boolean {
    return this.quarterArray.every((value) => value === null);
  }

  getPlayer() {
    this.fetchPlayers(this.quarterArray, this.usersQuarter);
    this.fetchPlayers(this.semiArray, this.usersSemi);
    this.fetchPlayers(this.finalArray, this.usersFinal);
  }

  fetchPlayers(sourceArray: any[], userArray: user[]) {
    for (let i = 0; i < sourceArray.length; i++) {
      if (sourceArray[i] !== null) {
        const playerId = sourceArray[i];
        const participant = this.global.matchPartecipants.value.find(
          (participant) => participant.id === playerId
        );
        if (participant !== undefined) {
          const avatar = participant.avatar;
          const id = participant.id;
          const username = participant.nick;
          userArray.push(new user(id, username, avatar));
        }
      } else {
        userArray.push(new user(-1, '', ''));
      }
    }
  }

  back() {
    this.router.navigate(['/lobby']);
  }

  shadowCard(id: number, stage: string) {
    if (this.turn === stage && id === Number(this.global.nextMatch[0]))
      return true;

    return false;
  }

  myTurn(id: number, stage: string) {
    if (
      (Number(this.global.nextMatch[0]) === this.global.user.getId() ||
        Number(this.global.nextMatch[1]) === this.global.user.getId()) &&
      this.global.user.getId() === id &&
      this.global.turn === stage
    ) {
      return true;
    }
    return false;
  }

  readyToPlay: boolean = false;
  nextMatchReady() {
    // //console.log(this.global.nextMatch[0], this.global.nextMatch);
    if (
      Number(this.global.nextMatch[0]) === this.global.user.getId() ||
      Number(this.global.nextMatch[1]) === this.global.user.getId()
    ) {
      this.readyToPlay = !this.readyToPlay;
      this.websocket.readyToPlayMatch(
        this.global.user.getId(),
        this.readyToPlay
      );
    }
    //  else {
    //   //console.log(
    //     'Attenzione! Puoi premere solamente ready relativo al tuo user'
    //   );
    // }
  }

  ready1: boolean = false;
  changeButton1(id: number) {
    if (this.userReady.id === id && Number(this.global.nextMatch[0]) === id) {
      this.ready1 = this.userReady.ready;
    }
    return this.ready1;
  }
  
  ready2: boolean = false;
  changeButton2(id: number) {
    if (this.userReady.id === id && Number(this.global.nextMatch[1]) === id) {
      this.ready2 = this.userReady.ready;
    }
    return this.ready2;
  }

  myOpponent(id: number) {
    if (Number(this.global.nextMatch[0]) === id || Number(this.global.nextMatch[1]) === id) { 
      return true;
    }
    return false;
  }
}

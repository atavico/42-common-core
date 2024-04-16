import { Component } from '@angular/core';
import { LocalGame } from '../local-game.service';
import { Router } from '@angular/router';

@Component({
  selector: 'app-tournament-local',
  templateUrl: './tournament-local.component.html',
  styleUrls: ['./tournament-local.component.css'],
})
export class TournamentLocalComponent {
  finalsStr: string = 'Finals';
  firstSecondPlaceStr: string = 'First and Second places';
  notMyTurn: string = 'Not my turn';
  semiFinalsStr: string = 'Semifinals';

  constructor(private localGame: LocalGame, private router: Router) {}

  usersFinal: { nick: string; avatar: string }[] = [];
  usersSemi: { nick: string; avatar: string }[] = [];

  turn: string = '';

  ngOnInit() {
    this.turn = this.localGame.turn;
    this.usersFinal = [
      {
        nick: this.localGame.finals[0][0],
        avatar:
          this.localGame.partecipants.find(
            (partecipant) => partecipant.nick === this.localGame.finals[0][0]
          )?.avatar || '',
      },
      {
        nick: this.localGame.finals[0][1],
        avatar:
          this.localGame.partecipants.find(
            (partecipant) => partecipant.nick === this.localGame.finals[0][1]
          )?.avatar || '',
      },
    ];
    this.usersSemi = [
      {
        nick: this.localGame.semifinals[0][0],
        avatar:
          this.localGame.partecipants.find(
            (partecipant) =>
              partecipant.nick === this.localGame.semifinals[0][0]
          )?.avatar || '',
      },
      {
        nick: this.localGame.semifinals[0][1],
        avatar:
          this.localGame.partecipants.find(
            (partecipant) =>
              partecipant.nick === this.localGame.semifinals[0][1]
          )?.avatar || '',
      },
      {
        nick: this.localGame.semifinals[1][0],
        avatar:
          this.localGame.partecipants.find(
            (partecipant) =>
              partecipant.nick === this.localGame.semifinals[1][0]
          )?.avatar || '',
      },
      {
        nick: this.localGame.semifinals[1][1],
        avatar:
          this.localGame.partecipants.find(
            (partecipant) =>
              partecipant.nick === this.localGame.semifinals[1][1]
          )?.avatar || '',
      },
    ];
  }

  shadowCard(nick: string, stage: string) {
    if (
      this.turn === stage &&
      (nick === this.localGame.nextMatch.nick1 ||
        nick === this.localGame.nextMatch.nick2)
    )
      return true;
    return false;
  }

  myTurn(nick: string, stage: string) {
    if (
      this.turn === stage &&
      (nick === this.localGame.nextMatch.nick1 ||
        nick === this.localGame.nextMatch.nick2)
    )
      return true;
    return false;
  }

  readyToPlay1: boolean = false;
  readyToPlay2: boolean = false;
  nextMatchReady(id: number) {
    if (id === 1) this.readyToPlay1 = !this.readyToPlay1;
    else this.readyToPlay2 = !this.readyToPlay2;

    if (this.readyToPlay1 && this.readyToPlay2) {
      this.router.navigate(['/match-local']);
    }
  }
}

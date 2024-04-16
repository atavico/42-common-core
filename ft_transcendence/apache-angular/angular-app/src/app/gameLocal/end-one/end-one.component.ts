import { Component } from '@angular/core';
import { LocalGame } from '../local-game.service';
import { AudioService } from 'src/app/service/audio.service';
import { Router } from '@angular/router';
import { GameService } from 'src/app/service/game.service';
import { Global } from 'src/app/shared/global';

@Component({
  selector: 'app-end-one',
  templateUrl: './end-one.component.html',
  styleUrls: ['./end-one.component.css'],
})
export class EndOneComponent {
  backHome: string = 'Go back home';
  winnerStr: string = 'The winner is: ';
  winnerAvatar: string = '';
  winnerNick: string = '';

  constructor(
    private localGame: LocalGame,
    private audioService: AudioService,
    private router: Router,
    private gameService: GameService,
    private global: Global
  ) {}

  ngOnInit(): void {
    if (this.localGame.score[0] > this.localGame.score[1]) {
      this.winnerAvatar = this.localGame.nextMatch.avatar1;
      this.winnerNick = this.localGame.nextMatch.nick1;
    } else {
      this.winnerAvatar = this.localGame.nextMatch.avatar2;
      this.winnerNick = this.localGame.nextMatch.nick2;
    }

    let body = {
      user_id: this.global.user.getId(),
      winner: this.winnerNick,
      player1: this.localGame.nextMatch.nick1,
      player2: this.localGame.nextMatch.nick2,
      p1_score: this.localGame.score[0],
      p2_score: this.localGame.score[1],
      tournament_game: false,
      tournament_stage: '',
    };
    this.gameService.postLocalMatch(body).subscribe((data: any) => {
      console.log('match saved: ', data);
    });
    this.localGame.cleanClass();
  }

  onBackHome() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.router.navigate(['/main-menu']);
  }
}

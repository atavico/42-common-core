import { Component, HostListener } from '@angular/core';
import { LocalGame } from '../local-game.service';
import { MatchLocalService } from '../local-game.service';
import { Router } from '@angular/router';

@Component({
  selector: 'app-match-local',
  templateUrl: './match-local.component.html',
  styleUrls: ['./match-local.component.css'],
})
export class MatchLocalComponent {
  constructor(private localGame: LocalGame, private router: Router) {}

  player1Nick: string = this.localGame.nextMatch.nick1;
  player2Nick: string = this.localGame.nextMatch.nick2;
  player1Avatar: string = this.localGame.nextMatch.avatar1;
  player2Avatar: string = this.localGame.nextMatch.avatar2;
  score1: number = 0;
  score2: number = 0;

  paddle_1: { [key: string]: string } = { top: '50%' };
  paddle_2: { [key: string]: string } = { top: '50%' };
  ballMovement: { [key: string]: string } = { left: '50%', top: '50%' };

  p1_paddle: any;
  p2_paddle: any;

  match: MatchLocalService = new MatchLocalService();

  @HostListener('window:keydown', ['$event'])
  handleKeyDown(event: KeyboardEvent) {
    this.match.key_pressed(event.key, true);
  }

  @HostListener('window:keyup', ['$event'])
  handleKeyUp(event: KeyboardEvent) {
    this.match.key_pressed(event.key, false);
  }

  gameLoop() {
    this.checkAndStopPaddleMovement();
    this.match.move_ball_and_collide();
    this.setObjectsPosition();

    if (this.score1 == 3 || this.score2 == 3) {
      if (this.checkSetTournament(this.localGame.idMatch) == true) {
        console.log('checkSetTournament');

        this.setNextMatch(this.localGame.idMatch);
        this.router.navigate(['/tournament-local']);
      } else {
        this.localGame.score = [this.score1, this.score2];
        this.router.navigate(['/end-one']);
      }
    } else {
      requestAnimationFrame(() => this.gameLoop());
    }
  }

  checkSetTournament(idMatch: number = 0) {
    if (this.localGame.tournementOrSolo == true) {
      if (this.score1 == 3) {
        this.localGame.finals[0][idMatch] = this.player1Nick;
      } else {
        this.localGame.finals[0][idMatch] = this.player2Nick;
      }
      if (this.localGame.idMatch == 2) return false;
      this.localGame.idMatch++;
      return true;
    }
    return false;
  }

  setNextMatch(idMatch: number = 0) {
    if (idMatch == 1) {
      if (this.localGame.semifinals[1][1] != '') {
        this.localGame.nextMatch = {
          nick1: this.localGame.semifinals[1][0],
          avatar1:
            this.localGame.partecipants.find(
              (participant) =>
                participant.nick === this.localGame.semifinals[1][0]
            )?.avatar || '',
          nick2: this.localGame.semifinals[1][1],
          avatar2:
            this.localGame.partecipants.find(
              (participant) =>
                participant.nick === this.localGame.semifinals[1][1]
            )?.avatar || '',
        };
      } else {
        this.score1 = 3;
        this.player1Nick = this.localGame.semifinals[1][0];
        this.checkSetTournament(idMatch);
      }
    }
    if (this.localGame.idMatch == 2) {
      console.log('setNextMatch');
      this.localGame.turn = 'finals';
      this.localGame.nextMatch = {
        nick1: this.localGame.finals[0][0],
        avatar1:
          this.localGame.partecipants.find(
            (participant) => participant.nick === this.localGame.finals[0][0]
          )?.avatar || '',
        nick2: this.localGame.finals[0][1],
        avatar2:
          this.localGame.partecipants.find(
            (participant) => participant.nick === this.localGame.finals[0][1]
          )?.avatar || '',
      };
    }
  }

  setObjectsPosition() {
    let pos = this.match.dict();
    this.paddle_1['top'] = pos.paddles_y[0].toString() + '%';
    this.paddle_2['top'] = pos.paddles_y[1].toString() + '%';
    this.ballMovement['left'] = pos.ball_pos[0].toString() + '%';
    this.ballMovement['top'] = pos.ball_pos[1].toString() + '%';
    this.score1 = pos.score[0];
    this.score2 = pos.score[1];
  }

  ngOnInit() {
    this.p1_paddle = document.getElementById("p1_paddle");
    this.p2_paddle = document.getElementById("p2_paddle");
    this.gameLoop();
  }

  /* ------------------------------------------------
  // Mobile Touch Implementation
  ------------------------------------------------ */

  p1_moving: boolean = false;
  p2_moving: boolean = false;
  p1_touchY: number = 0.0;
  p2_touchY: number = 0.0;
  p1_key: string = '';
  p2_key: string = '';

  getPaddleProperties(paddle_id: number){
    let pdl = {
      top: 0,
      height: 0,
      center_pos: 0,
    }
    let arr = [this.p1_paddle, this.p2_paddle];
    let p: any = arr[paddle_id];
    if (p != null) {
      pdl.top = p.getBoundingClientRect().top;
      pdl.height = p.getBoundingClientRect().height;
      pdl.center_pos = pdl.top + (pdl.height / 2);
      return pdl;
    }
    return null;
  }

  checkAndStopPaddleMovement() {
    let arr: any = [this.p1_paddle, this.p2_paddle]
    for (let i in [0, 1]) {
      let p: any = this.getPaddleProperties(Number(i));
      if (p != null) {
        if (Number(i) === 0 && p.center_pos < (this.p1_touchY + 5) && p.center_pos > (this.p1_touchY - 5))
        {  
          this.match.key_pressed(this.p1_key, false);
        }
        else if (Number(i) === 1 && p.center_pos < (this.p2_touchY + 5) && p.center_pos > (this.p2_touchY - 5))
        { 
          this.match.key_pressed(this.p2_key, false);
        }
      }
    }
  }

  // listen to touch drag inputs
  @HostListener('window:touchmove', ['$event'])
  handleTouchMove(event: TouchEvent){
    let touchY = event.touches[0].clientY;
    let touchX = event.touches[0].clientX;

    let paddle_i = 0;
    if (touchX > window.innerWidth / 2)
      paddle_i = 1;

    const paddle_prop = this.getPaddleProperties(paddle_i);
    if (paddle_prop == null)
      return ;

    const displacement = paddle_prop.center_pos - touchY;

    if (Math.abs(displacement) > 10) {
      let key: string;
      if (paddle_i == 0)
      {
        key = displacement > 0 ? 'w' : 's';
        this.p1_touchY = touchY;
        this.p1_key = key;
        console.log("p1 touched Y: ", this.p1_touchY, " | X: ", touchX);
      }
      else
      {
        key = displacement > 0 ? 'ArrowUp' : 'ArrowDown';
        this.p2_touchY = touchY;
        this.p2_key = key;
        console.log("p2 touched Y: ", this.p2_touchY, " | X: ", touchX);
      }
      this.match.key_pressed(key, true);
    }
  }

  @HostListener('window:touchend', ['$event'])
  handleTouchEnd(event: TouchEvent) {
      this.match.key_pressed(this.p1_key, false);
      this.match.key_pressed(this.p2_key, false);
  }

}

// gameLoop() {
//   if (this.keys['ArrowUp'] && parseFloat(this.paddle_2['top']) > 0) {
//     // Move paddle 2 up
//     this.paddle_2['top'] = (parseFloat(this.paddle_2['top']) - 0.5) + '%';
//   }
//   if (this.keys['ArrowDown'] && parseFloat(this.paddle_2['top']) < 90) {
//     // Move paddle 2 down
//     this.paddle_2['top'] = (parseFloat(this.paddle_2['top']) + 0.5) + '%';
//   }
//   if (this.keys['w'] && parseFloat(this.paddle_1['top']) > 0) {
//     // Move paddle 1 up
//     this.paddle_1['top'] = (parseFloat(this.paddle_1['top']) - 0.5) + '%';
//   }
//   if (this.keys['s'] && parseFloat(this.paddle_1['top']) < 90) {
//     // Move paddle 1 down
//     this.paddle_1['top'] = (parseFloat(this.paddle_1['top']) + 0.5) + '%';
//   }

//   requestAnimationFrame(() => this.gameLoop());
// }

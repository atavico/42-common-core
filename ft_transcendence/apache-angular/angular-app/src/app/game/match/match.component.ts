import { NgStyle } from '@angular/common';
import { Component, HostListener, OnInit, AfterViewInit } from '@angular/core';
import { BehaviorSubject, Subscription } from 'rxjs';
import { WebsocketService } from 'src/app/service/websocket.service';
import { RefreshGame } from 'src/app/shared/global';
import { Global } from 'src/app/shared/global';
import { FriendService } from 'src/app/service/friend.service';

@Component({
  selector: 'app-match',
  templateUrl: './match.component.html',
  styleUrls: ['./match.component.css'],
})
export class MatchComponent implements OnInit {
  lastArrow: string = '';
  buttonPressed: boolean = false;
  isPressed: boolean = false;

  ballMovement: { [key: string]: string } = { left: '50%', top: '50%' };
  paddle_1: { [key: string]: string } = { top: '50%' };
  paddle_2: { [key: string]: string } = { top: '50%' };
  private subscription: Subscription = new Subscription();

  user_1_avatar: string = '';
  user_1_nick: string = '';
  user_2_avatar: string = '';
  user_2_nick: string = '';

  i_am_p1: boolean = true;

  p1_paddle: any;
  p2_paddle: any;

  constructor(
    private websocketService: WebsocketService,
    private global: Global,
    private friendservice: FriendService
  ) {}

  ngAfterViewInit() {
    const ref1 = document.getElementById('user1');
    const ref2 = document.getElementById('user2');
    if (ref1 && ref2) {
      //console.log('user1: ', this.user_1_nick);
      //console.log('user2: ', this.user_2_nick);
      ref1.textContent = this.user_1_nick;
      ref2.textContent = this.user_2_nick;
    }
  }
  
  ngOnInit(): void {
      //player1
      this.p1_paddle = document.getElementById("p1_paddle");
      const user1 = this.global.IdPartecipants[0];
      const user_1_id = '#' + this.global.IdPartecipants[0].toString();
      this.friendservice.getUserID(user1).subscribe((data: any) => {
        this.user_1_nick = data.data.username;
        this.user_1_avatar = data.data.avatar;
        const ref1 = document.getElementById('user1');
        if(ref1) {
          ref1.textContent = this.user_1_nick;
        }
        //console.log('user1_id: ', data);

      });
      
      //player2
      this.p2_paddle = document.getElementById("p2_paddle");
      const user2 = this.global.IdPartecipants[1];
      const user_2_id = '#' + this.global.IdPartecipants[1].toString();
      
      this.friendservice.getUserID(user2).subscribe((data: any) => {
        this.user_2_nick = data.data.username;
        this.user_2_avatar = data.data.avatar;
        const ref2 = document.getElementById('user2');
        if(ref2) {
          ref2.textContent = this.user_2_nick;
        }
        //console.log('user2_id: ', data);
      });

    if (this.global.IdPartecipants[0] === this.global.user.getId())
      this.i_am_p1 = true;
    else
      this.i_am_p1 = false;

    //game refresh
    this.websocketService.getRefreshGame().subscribe((data: any) => {
      if (data.action === 'game_refresh') {
        //ball
        this.ballMovement = {
          left: data.match.ball_pos[0].toString() + '%',
          top: data.match.ball_pos[1].toString() + '%',
        };
        //paddles
        this.check_paddle_movement();
        this.paddle_1 = {top: data.match.paddles_y[0].toString() + '%'};
        this.paddle_2 = {top: data.match.paddles_y[1].toString() + '%'};
        //score
        const s = data.match.score;
        const ref = document.getElementById('score');

        if (ref) {
          ref.textContent = s[0] + ' - ' + s[1];
        }
      }
    });
  }

  getPaddleProperties(){
    let pdl = {
      top: 0,
      height: 0,
      center_pos: 0,
    }
    let arr: any = [this.p1_paddle, this.p2_paddle]
    for (let i in [this.p1_paddle, this.p2_paddle]) {
      let p: any = arr[i];
      if (p != null && ((this.i_am_p1 && Number(i) === 0) || (this.i_am_p1 === false && Number(i) === 1))){
        pdl.top = p.getBoundingClientRect().top;
        pdl.height = p.getBoundingClientRect().height;
        pdl.center_pos = pdl.top + (pdl.height / 2);
        return pdl;
      }
    }
    return null;
  }

  check_paddle_movement(){
    let arr: any = [this.p1_paddle, this.p2_paddle]
    for (let i in [this.p1_paddle, this.p2_paddle]) {
      let p: any = arr[i];
      if (p != null && ((this.i_am_p1 && Number(i) === 0) || (this.i_am_p1 === false && Number(i) === 1))){
        let top = p.getBoundingClientRect().top;
        let height = p.getBoundingClientRect().height;
        let center_pos = top + (height / 2);
        if (center_pos < (this.touchStartY + 5) && center_pos > (this.touchStartY - 5))
        {
          this.handleReachedEnd();
        }
      }
    }
  }

  @HostListener('window:keydown', ['$event'])
  @HostListener('window:touchstart', ['$event'])
  handleKeyboardEvent(event: KeyboardEvent | TouchEvent) {
    if (
      !this.buttonPressed &&
      event instanceof KeyboardEvent &&
      (event.key === 'ArrowUp' || event.key === 'ArrowDown')
    ) {
      this.lastArrow = event.key;
      this.buttonPressed = true;
      this.websocketService.key_event(this.lastArrow, this.buttonPressed);
    }
  }

  @HostListener('window:keyup', ['$event'])
  @HostListener('window:touchend', ['$event'])
  handleKeyboardUpEvent(event: KeyboardEvent | TouchEvent) {
    if (
      event instanceof KeyboardEvent &&
      (event.key === 'ArrowUp' || event.key === 'ArrowDown')
    ) {
      this.lastArrow = event.key;
      this.buttonPressed = false;
      this.websocketService.key_event(this.lastArrow, this.buttonPressed);
    }
  }

  private touchStartY: number = 0;
  @HostListener('window:touchstart', ['$event'])
  handleTouchStart(event: TouchEvent) {
    this.touchStartY = event.touches[0].clientY;
  }

  @HostListener('window:touchmove', ['$event'])
  handleTouchMove(event: TouchEvent) {
    const touchMoveY = event.touches[0].clientY;
    const paddle_prop = this.getPaddleProperties();
    if (paddle_prop === null)
      return ;
    const displacement = paddle_prop.center_pos - touchMoveY;
    
    if (Math.abs(displacement) > 10) {
      let oldArrow = this.lastArrow;
      this.lastArrow = displacement > 0 ? 'ArrowUp' : 'ArrowDown';
      this.touchStartY = touchMoveY;
      if (this.buttonPressed === false || oldArrow !== this.lastArrow)
      {
        this.buttonPressed = true;
        this.websocketService.key_event(this.lastArrow, this.buttonPressed);
      }
    }
  }

  @HostListener('window:touchend', ['$event'])
  handleTouchEnd(event: TouchEvent) {
    this.touchStartY = 0;
    if (this.buttonPressed === true)
    {
      this.buttonPressed = false;
      this.websocketService.key_event(this.lastArrow, this.buttonPressed);
    }
  }

  handleReachedEnd() {
    this.touchStartY = 0;
    if (this.buttonPressed === true)
    {
      this.buttonPressed = false;
      this.websocketService.key_event(this.lastArrow, this.buttonPressed);
    }
  }
}

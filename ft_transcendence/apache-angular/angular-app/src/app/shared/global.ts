import { Injectable } from '@angular/core';
import { User } from './user';
import { Tournament } from '../game/tournament';
import { catchError } from 'rxjs/operators';
import { throwError, Observable, BehaviorSubject } from 'rxjs';
import { FriendService } from 'src/app/service/friend.service';

import { user } from 'src/app/game/tournament-pre/user.model';

interface OnlineUsers {
  action: string;
  active_users: number[];
  left: boolean;
  event_user_id: number;
}

export interface Partecipant {
  id: number;
  nick: string;
  avatar: string;
  ready: boolean;
}

export interface RefreshGame {
  score: number[];
  paddles_y: number[];
  ball_pos: string[];
  ball_speed: number;
  ball_dir: number;
}

export interface structure {
  finals: string[];
  semifinals: string[];
  quarterfinals: string[];
}

export interface winners {
  finals: string[];
  semifinals: string[];
  quarterfinals: string[];
}

@Injectable()
export class Global {
  constructor(private friendService: FriendService) {
    this.onlineUsers = {
      action: '',
      active_users: [],
      left: false,
      event_user_id: 0,
    };
  }

  user: User = new User();
  isLogged: boolean = false;
  onlineUsers: OnlineUsers;
  currentGame: Tournament = new Tournament();
  matchPartecipants: BehaviorSubject<Partecipant[]> = new BehaviorSubject<
    Partecipant[]
  >([]);

  finals: string[][] = [
    ['', ''],
    ['', ''],
  ];
  semifinals: string[][] = [
    ['', ''],
    ['', ''],
  ];
  quarter: string[][] = [
    ['', ''],
    ['', ''],
    ['', ''],
    ['', ''],
  ];

  quarterWinner: string[] = ['', '', '', ''];
  semiWinner: string[] = ['', ''];
  finalWinner: string[] = [''];

  placements: string[] = [];

  usersQuarter: user[] = [];
  usersSemi: user[] = [];
  usersFinal: user[] = [];

  turn: string = '';
  isTournament: boolean = false;
  tournamentID: number = -1;

  userGameReady: {
    id: number;
    ready: boolean;
  } = { id: -1, ready: false };

  // Blockchain data
  IdMatch_B: number = 0;
  finals_B: string[][] = [
    ['', ''],
    ['', ''],
  ];
  semifinals_B: string[][] = [
    ['', ''],
    ['', ''],
  ];
  quarter_B: string[][] = [
    ['', ''],
    ['', ''],
    ['', ''],
    ['', ''],
  ];
  wf_B: string[] = [];
  ws_B: string[] = [];
  wq_B: string[] = [''];
  hash_tx: string = '';

  nextMatch: string[] = ['1', '2'];

  IdPartecipants: number[] = [];

  userMap: Map<string, string> = new Map<string, string>();
  getUsers() {
    this.friendService
      .getAllUsers()
      .pipe(
        catchError((error: any): Observable<never> => {
          //console.log('error in GetAllUsers: ', error);
          return throwError(() => error);
        })
      )
      .subscribe((data) => {
        for (let key in data.data) {
          this.userMap.set(key, data.data[key]);
        }
        //console.log('userMap: ', this.userMap);
      });
  }
}

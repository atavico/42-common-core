import { Component } from '@angular/core';
import { BehaviorSubject, Observable } from 'rxjs';
import { GameService } from 'src/app/service/game.service';
import { WebsocketService } from 'src/app/service/websocket.service';
import { Tournament } from '../tournament';
import { Global } from 'src/app/shared/global';
import { FormControl } from '@angular/forms';
import { Router } from '@angular/router';
import { AudioService } from 'src/app/service/audio.service';
import { LanguageService } from 'src/app/service/language.service';

@Component({
  selector: 'app-host-menu',
  templateUrl: './host-menu.component.html',
  styleUrls: ['./host-menu.component.css'],
})
export class HostMenuComponent {
  // HTML variables
  publicStr: string = 'Public';
  privateStr: string = 'Private';
  onlyFriendsStr: string = 'Only friends';
  selectStr: string = 'Select number of participants: ';
  scoreStr: string = 'Select score to win: ';
  back: string = 'Back';
  hostMatchStr: string = 'Host match';
  createPasswordStr: string = 'Create a password';

  constructor(
    private router: Router,
    private gameService: GameService,
    private websocketService: WebsocketService,
    private global: Global,
    private audioService: AudioService,
    private languageService: LanguageService
  ) {}

  ngOnInit(): void {
    this.updateLocalizedStrings();
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[localStorage.getItem('language') || 'en'];
      const keysToUpdate = [
        'publicStr',
        'privateStr',
        'onlyFriendsStr',
        'selectStr',
        'scoreStr',
        'back',
        'hostMatchStr',
        'createPasswordStr',
      ];
      for (let key of keysToUpdate) {
        if (langData.hasOwnProperty(key)) {
          this[key] = langData[key];
        }
      }
    });
  }

  selectedValue: number = 2;
  matchTypeSubject: BehaviorSubject<string> = new BehaviorSubject<string>(
    '1 vs 1'
  );
  matchType: Observable<string> = this.matchTypeSubject.asObservable();

  selectedScore: number = 2;
  selectedColor: string = '#121212';
  onlyFriends: boolean = false;

  code = new FormControl('');

  publicOrPrivate: string = 'public';
  selectMatchType(value: string): void {
    this.audioService.playAudio(this.audioService.clickButton);
    this.publicOrPrivate = value;
    if (this.publicOrPrivate === 'private') {
      this.onlyFriends = true;
    } else {
      this.onlyFriends = false;
    }
  }

  onSliderChange(value: number): void {
    this.selectedValue = value;
    if (this.selectedValue === 2) {
      this.matchTypeSubject.next('1 vs 1');
    } else {
      this.matchTypeSubject.next('Tournament');
    }
  }

  gameOptions = false;
  option = {
    type: this.matchTypeSubject.value,
    players: this.selectedValue,
    'public||private': this.publicOrPrivate,
  };

  match: Tournament = {} as Tournament;

  createMatch(): void {
    // if (!this.publicOrPrivate) {
    //   alert('Per favore, seleziona pubblico o privato prima di creare un match.');
    //   return;
    // }
    // Play audio
    this.audioService.playAudio(this.audioService.clickButton);

    this.match = {
      tournament_name: 'Tournament X',
      game_type: this.matchTypeSubject.value,
      friends_only: this.onlyFriends,
      password: false,
      score_to_win: this.selectedScore,
      max_partecipants: this.selectedValue,
      creator: this.global.user.getId(),
      status: 'pending',
      players_id: '[]',
      placements: '[]',
      is_active: true,
    };
    this.global.currentGame = this.match;
    this.gameService.createMatch(this.match).subscribe((data: any) => {
      //console.log('matchCreated: ', data);
      const matchId: number = data.data.id;
      const psw: string = data.data.password;
      const obs = false;
      //console.log('matchId: ', matchId);
      this.global.tournamentID = matchId;
      this.websocketService.initializeTournamentSocket(matchId, '', obs).subscribe((data) => {
        if (data.action != "game_refresh"){
          //console.log('Data received by tournamentSocket: ', data);
        };
      });
    });
    this.router.navigate(['/queue']);
  }

  backClick(): void {
    this.audioService.playAudio(this.audioService.clickButton);
    this.router.navigate(['/lobby']);
  }
}

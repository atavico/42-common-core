// angular imports
import { Component, OnInit } from '@angular/core';
import { NavigationEnd, NavigationStart, Router } from '@angular/router';
// other
import { Global } from '../shared/global';
import { WebsocketService } from '../service/websocket.service';

@Component({
  selector: 'app-main-menu',
  templateUrl: './main-menu.component.html',
})
export class MainMenuComponent implements OnInit {
  selectedChannel: string = 'online-users';
  message: string = '';

  currentGameMoves: string[] = [];
  tournamentGames: string[] = [];

  constructor(
    private global: Global,
    private websocket: WebsocketService,
    private router: Router
    ) {}

  // private getUsersIntervalId: any;
  ngOnInit(): void {
    
    // this.router.events.subscribe((event) => {
    //   if (event instanceof NavigationStart) {
    //     this.websocket.closeTournamentWebSocket();
    //   }
    // });
    localStorage.setItem('language', this.global.user.getLanguage() || 'en');
    // Get all Users from database
    this.global.getUsers();
  }
}

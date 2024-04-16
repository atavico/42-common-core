import { Component, OnDestroy, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { AudioService } from 'src/app/service/audio.service';
import { Global } from 'src/app/shared/global';
import { BehaviorSubject, Observable, Subject } from 'rxjs';
import { Partecipant } from 'src/app/shared/global';
import { WebsocketService } from 'src/app/service/websocket.service';
import { LanguageService } from 'src/app/service/language.service';

@Component({
  selector: 'app-queue',
  templateUrl: './queue.component.html',
  styleUrls: ['./queue.component.css'],
})
export class QueueComponent implements OnInit {
  // HTML variables
  organizingStr: string = 'Organizing tournament event';
  waitingStr: string = 'Waiting for all challengers';

  max_partecipants: number;
  ready: Subject<boolean> = new Subject<boolean>();
  partecipants: BehaviorSubject<Partecipant[]> = new BehaviorSubject<
    Partecipant[]
  >([]);
  currentPartecipants: number = 1;

  constructor(
    private router: Router,
    private audioService: AudioService,
    public global: Global,
    private websocket: WebsocketService,
    private languageService: LanguageService,
  ) {
    this.global.matchPartecipants.subscribe((partecipants) => {
      //console.log('partecipants: ', partecipants);
      this.partecipants.next(partecipants);
      this.currentPartecipants = partecipants.length;
    });
    this.max_partecipants = this.global.currentGame?.max_partecipants || 0;
  }

  ngOnInit(): void {
    this.global.isTournament = false;

    this.updateLocalizedStrings();
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[this.global.user.getLanguage() ?? 'en'];
      const keysToUpdate = [
        'organizingStr',
        'waitingStr',
      ];
      for (let key of keysToUpdate) {
        if (langData.hasOwnProperty(key)) {
          this[key] = langData[key];
        }
      }
    });
  }

  // ngOnDestroy() {
  //   //this.websocket.closeTournamentWebSocket();
  //   this.removeCurrentUserFromPartecipants();
  //   this.websocket.resetTournamentSocket();
  // }

  onReadyClick(partecipant: Partecipant) {
    if (partecipant.id === this.global.user.getId()) {
      partecipant.ready = !partecipant.ready;
      //console.log(partecipant.ready);
      this.websocket.readyToPlay(partecipant.id, partecipant.ready);
    } else {
      //console.log(
      //   'Attenzione! Puoi premere solamente ready relativo al tuo user'
      // );
    }
    //this.ready.next(true);
  }

  generateRange(n: number): number[] {
    return Array(n)
      .fill(0)
      .map((_, i) => i);
  }

  back() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.router.navigate(['/host-menu']);
  }
}

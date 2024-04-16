// angular imports
import { Component } from '@angular/core';
import { Router } from '@angular/router';
// service
import { AudioService } from '../../service/audio.service';
import { UpdateService } from '../../service/update.service';

@Component({
  selector: 'app-play-button',
  templateUrl: './play-button.component.html',
  styleUrls: ['./play-button.component.css'],
})
export class PlayButtonComponent {
  playRStr: string = 'Play Remote';
  playLStr: string = 'Play Local';

  constructor(
    private router: Router,
    private audioService: AudioService,
    private updateService: UpdateService
  ) {}

  ngOnInit() {
    this.updateService.updateNeeded$.subscribe(() => {
      let lang = localStorage.getItem('language');
      if (lang === 'en') this.playRStr = 'Play Remote';
      else if (lang === 'pl') this.playRStr = 'Graj na odległość';
      else if (lang === 'it') this.playRStr = 'Gioca a distanza';
      if (lang === 'en') this.playLStr = 'Play Local';
      else if (lang === 'pl') this.playLStr = 'Graj lokalnie';
      else if (lang === 'it') this.playLStr = 'Gioca localmente';
    });
  }

  openLobbyT() {
    this.audioService.playAudio(this.audioService.clickButton);

    this.router.navigate(['/lobby']);
  }

  openLobbyL() {
    this.audioService.playAudio(this.audioService.clickButton);

    this.router.navigate(['/lobby-local']);
  }
}

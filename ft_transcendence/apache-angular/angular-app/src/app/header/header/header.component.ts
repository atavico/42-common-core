import { Component } from '@angular/core';
import { AudioService } from 'src/app/service/audio.service';

@Component({
  selector: 'app-header',
  templateUrl: './header.component.html',
  styleUrls: ['./header.component.css'],
})
export class HeaderComponent {
  audioSwitch: boolean = false;
  isPreviousDisabled: boolean = false;
  isNextDisabled: boolean = false;
  volume: number = 0.3;

  constructor(private audioService: AudioService) {}

  ngOnInit(): void {
    if (localStorage.getItem('volume')) {
      this.volume = parseFloat(localStorage.getItem('volume')!);
      if (this.volume < 0.1) return;
      this.audioService.playBackgroundMusic();
      this.adjustVolume();
      this.audioSwitch = true;
    }
  }

  onPrevious() {
    if (!this.isPreviousDisabled && this.audioSwitch) {
      this.isPreviousDisabled = true;
      this.audioService.previousTrack();
      setTimeout(() => {
        this.isPreviousDisabled = false;
      }, 2000);
    }
  }

  onToggle() {
    this.audioSwitch = !this.audioSwitch;
    if (this.audioSwitch) {
      this.audioService.playBackgroundMusic();
      this.adjustVolume();
    } else {
      this.audioService.pauseBackgroundMusic();
    }
  }

  onNext() {
    if (!this.isNextDisabled && this.audioSwitch) {
      this.isNextDisabled = true;
      this.audioService.nextTrack();
      setTimeout(() => {
        this.isNextDisabled = false;
      }, 2000);
    }
  }

  adjustVolume() {
    this.audioService.adjustVolume(this.volume);
    if (this.volume < 0.1) this.audioSwitch = false;
  }
}

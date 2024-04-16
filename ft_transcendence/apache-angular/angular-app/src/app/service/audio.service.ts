import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root',
})
export class AudioService {
  private audioMap = new Map<string, HTMLAudioElement>();
  volume: number = 0.3;

  // Path to audio files
  clickButton: string = 'assets/audio/click.wav';

  backMusic: string[] = [
    'assets/audio/background/1980.mp3',
    'assets/audio/background/arcade.mp3',
    'assets/audio/background/back-to-the-city.mp3',
    'assets/audio/background/one-step-ahead.mp3',
    'assets/audio/background/password-infinity.mp3',
    'assets/audio/background/synthwave-80s.mp3',
    'assets/audio/background/test-tube.mp3',
  ];

  currentBackgroundMusic: number = Math.floor(
    Math.random() * this.backMusic.length
  );

  constructor() {}

  ngOnInit(): void {
    if (localStorage.getItem('volume')) {
      this.volume = parseFloat(localStorage.getItem('volume')!);
    } else {
      localStorage.setItem('volume', this.volume.toString());
    }
  }

  // Play audio file from src path
  playAudio(src: string) {
    let audio = this.audioMap.get(src);
    if (!audio) {
      audio = this.createAudio(src);
      this.audioMap.set(src, audio);
    } else if (!audio.paused) {
      return;
    }
    audio.play().catch((error) => {
      //console.log('Audio playback failed:', error);
    });
  }

  pauseAudio(src: string) {
    let audio = this.audioMap.get(src);
    if (audio) {
      audio.pause();
    }
  }

  playBackgroundMusic() {
    let src = this.backMusic[this.currentBackgroundMusic];
    let audio = this.audioMap.get(src);
    if (!audio) {
      audio = this.createAudio(src);
      this.audioMap.set(src, audio);
    }
    audio.play().catch((error) => {
      //console.log('Audio playback failed:', error);
    });
    audio.onended = () => {
      this.currentBackgroundMusic =
        (this.currentBackgroundMusic + 1) % this.backMusic.length;
      this.playBackgroundMusic();
      this.adjustVolume(this.volume);
    };
  }

  pauseBackgroundMusic() {
    let src = this.backMusic[this.currentBackgroundMusic];
    let audio = this.audioMap.get(src);
    if (audio) {
      audio.pause();
    }
  }

  previousTrack() {
    // stop current track
    let src = this.backMusic[this.currentBackgroundMusic];
    let audio = this.audioMap.get(src);
    if (audio) {
      audio.pause();
      audio.currentTime = 0;
    }
    // play previous track
    this.currentBackgroundMusic =
      (this.currentBackgroundMusic - 1 + this.backMusic.length) %
      this.backMusic.length;
    this.playBackgroundMusic();
    this.adjustVolume(this.volume);
  }

  nextTrack() {
    // stop current track
    let src = this.backMusic[this.currentBackgroundMusic];
    let audio = this.audioMap.get(src);
    if (audio) {
      audio.pause();
      audio.currentTime = 0;
    }
    // play next track
    this.currentBackgroundMusic =
      (this.currentBackgroundMusic + 1) % this.backMusic.length;
    this.playBackgroundMusic();
    this.adjustVolume(this.volume);
  }

  adjustVolume(volume: number) {
    for (let audio of this.audioMap.values()) {
      audio.volume = volume;
      this.volume = volume;
      localStorage.setItem('volume', volume.toString());
      if (volume < 0.1) {
        this.pauseBackgroundMusic();
      }
    }
  }

  private createAudio(src: string): HTMLAudioElement {
    const audio = new Audio(src);
    return audio;
  }
}

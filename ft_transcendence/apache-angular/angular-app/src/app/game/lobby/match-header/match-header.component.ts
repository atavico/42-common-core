import { Component, EventEmitter, Input, Output } from '@angular/core';
import { AudioService } from 'src/app/service/audio.service';

@Component({
  selector: 'app-match-header',
  templateUrl: './match-header.component.html',
  styleUrls: ['./match-header.component.css'],
})
export class MatchHeaderComponent {
  @Input() matchType: string = '';
  @Input() switchWatchMatch: boolean = false;
  @Output() boolWatchMatch = new EventEmitter<boolean>();

  constructor(private audioService: AudioService) {}

  changePlayWatch() {
    this.boolWatchMatch.emit();
  }
}

import { Component, EventEmitter, Input, Output } from '@angular/core';
import { Match } from '../match.model';
import { Global } from 'src/app/shared/global';

@Component({
  selector: 'app-matches',
  templateUrl: './matches.component.html',
  styleUrls: ['./matches.component.css'],
})
export class MatchesComponent {
  @Input() match: Match = new Match(0, false, '', 0, false, 0, false, '', '', 0, '', '', '');
  @Input() JoinWatch: string = '';
  @Input() playerNbr: number = 0;
  @Output() joinMatch = new EventEmitter<Match>();

  friendInside: boolean = false;

  constructor(private global: Global) {}

  ngOnInit() {
    if (this.global.user.getFriendList().includes(Number(this.match.creator))) {
      this.friendInside = true;
    }
  }

  getCreator(creator: number) {
    return this.global.userMap.get(creator.toString());
  }

  joinToMatch(match: Match) {
    this.joinMatch.emit(match);
  }
}

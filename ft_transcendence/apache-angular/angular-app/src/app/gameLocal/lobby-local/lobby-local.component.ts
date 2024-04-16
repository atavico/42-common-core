import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { AudioService } from '../../service/audio.service';
import { LocalGame } from '../local-game.service';
import { Global } from 'src/app/shared/global';

@Component({
  selector: 'app-lobby-local',
  templateUrl: './lobby-local.component.html',
  styleUrls: ['./lobby-local.component.css'],
})
export class LobbyLocalComponent {
  animals = [
    'cat',
    'dog',
    'cow',
    'pig',
    'ant',
    'bat',
    'bee',
    'fox',
    'rat',
    'hen',
    'owl',
    'elk',
    'ape',
    'boa',
    'koi',
  ];

  avatarMap: { [key: string]: string } = {
    cat: 'assets/profilePic/cat.png',
    dog: 'assets/profilePic/dog.png',
    cow: 'assets/profilePic/cow.png',
    pig: 'assets/profilePic/pig.png',
    ant: 'assets/profilePic/ant.png',
    bat: 'assets/profilePic/bat.png',
    bee: 'assets/profilePic/bee.png',
    fox: 'assets/profilePic/fox.png',
    rat: 'assets/profilePic/rat.png',
    hen: 'assets/profilePic/hen.png',
    owl: 'assets/profilePic/owl.png',
    elk: 'assets/profilePic/elk.png',
    ape: 'assets/profilePic/ape.png',
    boa: 'assets/profilePic/boa.png',
    koi: 'assets/profilePic/koi.png',
  };

  players: { nick: string; avatar: string; id: number }[] = Array.from(
    { length: 4 },
    () => ({ nick: '', avatar: this.animals[0], id: 0 })
  );

  constructor(
    private router: Router,
    private audioService: AudioService,
    private localGame: LocalGame,
    private global: Global
  ) {
    this.players[0].nick = this.global.user.getNickname();
    this.players[0].avatar = this.global.user.getAvatar();
  }

  getEnteredPlayersCount(): number {
    return this.players.filter(
      (player) => player.nick && player.nick.trim() !== ''
    ).length;
  }

  errorPartecimants: boolean = false;
  errorSameNick: boolean = false;
  checkOnPlay() {
    if (this.getEnteredPlayersCount() < 2) {
      this.errorPartecimants = true;
      return false;
    }

    const seen: { [key: string]: boolean } = {};

    for (const player of this.players) {
      if (seen[player.nick] && player.nick !== '') {
        this.errorSameNick = true;
        return false;
      }
      seen[player.nick] = true;
    }

    return true;
  }

  onPlay() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.errorPartecimants = false;
    this.errorSameNick = false;

    if (this.checkOnPlay() === false) {
      return;
    }

    this.localGame.partecipants = this.players.filter(
      (player) => player.nick !== ''
    );
    this.localGame.partecipants.forEach((player, index) => {
      if (index === 0) {
        player.nick = this.global.user.getNickname();
        player.avatar = this.global.user.getAvatar();
      } else {
        let avatarImages = this.players.map(
          (player) => this.avatarMap[player.avatar]
        );
        player.avatar = avatarImages[index];
      }
      player.id = index;
    });
    console.log('partecipants', this.localGame.partecipants);

    if (this.localGame.partecipants.length === 2) {
      this.localGame.nextMatch = {
        nick1: this.localGame.partecipants[0].nick,
        avatar1: this.localGame.partecipants[0].avatar,
        nick2: this.localGame.partecipants[1].nick,
        avatar2: this.localGame.partecipants[1].avatar,
      };
      this.router.navigate(['/match-local']);
    } else {
      let shuffledPlayers = this.localGame.partecipants
        .map((player) => player.nick)
        .sort(() => Math.random() - 0.5);

      this.localGame.semifinals = [];
      for (let i = 0; i < shuffledPlayers.length; i += 2) {
        this.localGame.semifinals.push([
          shuffledPlayers[i],
          shuffledPlayers[i + 1] || '',
        ]);
      }
      this.localGame.nextMatch = {
        nick1: this.localGame.semifinals[0][0],
        avatar1:
          this.localGame.partecipants.find(
            (player) => player.nick === this.localGame.semifinals[0][0]
          )?.avatar || '',
        nick2: this.localGame.semifinals[0][1],
        avatar2:
          this.localGame.partecipants.find(
            (player) => player.nick === this.localGame.semifinals[0][1]
          )?.avatar || '',
      };
      this.localGame.turn = 'semifinals';
      this.localGame.tournementOrSolo = true;
      this.localGame.idMatch = 0;
      this.router.navigate(['/tournament-local']);
    }
  }

  onBack() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.router.navigate(['/main-menu']);
  }
}

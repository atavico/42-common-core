import { Component,OnDestroy, OnInit } from '@angular/core';
import { Subscription, first } from 'rxjs';
import { WebsocketService } from 'src/app/service/websocket.service';
import { Router } from '@angular/router';
import { Global } from 'src/app/shared/global';
import { FriendService } from 'src/app/service/friend.service';
import { HttpClient } from '@angular/common/http';
import { getBaseUrl } from 'src/app/shared/generic';
import { LanguageService } from 'src/app/service/language.service';

@Component({
  selector: 'app-end-game',
  templateUrl: './end-game.component.html',
  styleUrls: ['./end-game.component.css']
})

export class EndGameComponent {
  // HTML variables
  tourPlacementStr: string = 'Tournament placements';
  blockchainStr: string = 'All tournament scores are saved in ETH blockchain testnet';
  sepholiaViewStr: string = 'View transaction of this tournament on sepholia etherscan';
  requestBlockStr: string = 'Request tournament data from blockchain';
  quartersStr: string = 'Quarters';
  semiFinalsStr: string = 'Semifinals';
  finalsStr: string = 'Finals';
  blockchainDataStr: string = 'Blockchain data storage';
  winnerStr: string = 'Winner';
  backHome: string = 'Back to home';

  constructor(
    private websocket: WebsocketService,
    private router: Router,
    private global: Global,
    private friendservice: FriendService,
    private http: HttpClient,
    private languageService: LanguageService
    ) {}

    quarterArray: string[][] = [];
    semiArray: string[][] = [['1', '2'], ['3', '4']];
    finalArray: string[][] = [['1', '2'], ['3', '4']];

    qWin: string[] = [];
    sWin: string[] = ['2', '4'];
    fWin: string[] = ['1', '3'];
    winner: string = '1';

    winnerId: string = '';
    winnerAvatar: string = '';
    winnerNick: string = '';

    firstNick: string = '';
    secondNick: string = '';
    thirdNick: string = '';
    firstAvatar: string = '';
    secondAvatar: string = '';
    thirdAvatar: string = '';
    firstID: string = '';
    secondID: string = '';
    thirdID: string = '';

    isTour: boolean = true;

  ngOnInit() {
    this.updateLocalizedStrings();

      this.isTour = this.global.isTournament;
      this.winnerId = this.global.finalWinner[1];

      this.friendservice.getUserID(+this.winnerId).subscribe((data: any) => {
        this.winnerNick = data.data.username;
        this.winnerAvatar = data.data.avatar;
        const nick = document.getElementById('username-winner');
        if (nick) {
          nick.textContent = this.winnerNick;
        }
        const id = document.getElementById('id-winner');
        if (id) {
          id.textContent = '#' + this.winnerId;
        }
      });
      if (!isNaN(Number(this.global.placements[0]))) {
        this.friendservice.getUserID(+this.global.placements[0]).subscribe((data: any) => {
          this.firstID = '#' + this.global.placements[0];
          this.firstNick = data.data.username;
          this.firstAvatar = data.data.avatar;
          const firstIDref = document.getElementById('id-first');
          if (firstIDref) {
            firstIDref.textContent = this.firstID;
          }
          const firstNickref = document.getElementById('username-first');
          if (firstNickref) {
            firstNickref.textContent = this.firstNick;
          }
        });
      } else {
        // console.error('Invalid placement data');
      }
      if (!isNaN(Number(this.global.placements[1]))) {
        this.friendservice.getUserID(+this.global.placements[1]).subscribe((data: any) => {
          this.secondID = '#' + this.global.placements[1];
          this.secondNick = data.data.username;
          this.secondAvatar = data.data.avatar;
          const secondIDref = document.getElementById('id-second');
          if (secondIDref) {
            secondIDref.textContent = this.secondID;
          }
          const secondNickref = document.getElementById('username-second');
          if (secondNickref) {
            secondNickref.textContent = this.secondNick;
          }
        });
      } else {
        // console.error('Invalid placement data');
      }
      if (!isNaN(Number(this.global.placements[2]))) {
        this.friendservice.getUserID(+this.global.placements[2]).subscribe((data: any) => {
          this.thirdID = '#' + this.global.placements[2];
          this.thirdNick = data.data.username;
          this.thirdAvatar = data.data.avatar;
          const thirdIDref = document.getElementById('id-third');
          if (thirdIDref) {
            thirdIDref.textContent = this.thirdID;
          }
          const thirdNickref = document.getElementById('username-third');
          if (thirdNickref) {
            thirdNickref.textContent = this.thirdNick;
          }
        });
      } else {
        // console.error('Invalid placement data');
      }
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[this.global.user.getLanguage() ?? 'en'];
      const keysToUpdate = [
        'tourPlacementStr',
        'blockchainStr',
        'sepholiaViewStr',
        'requestBlockStr',
        'quartersStr',
        'semiFinalsStr',
        'finalsStr',
        'blockchainDataStr',
        'winnerStr',
        'backHome'
      ];
      for (let key of keysToUpdate) {
        if (langData.hasOwnProperty(key)) {
          this[key] = langData[key];
        }
      }
    });
  }

    allValuesNull(): boolean {
      for (let i = 0; i < this.quarterArray.length; i++) {
        if (this.quarterArray[i] !== null) {
          for (let j = 0; j < this.quarterArray[i].length; j++) {
            if (this.quarterArray[i][j] !== '' && this.quarterArray[i][j] !== ',') {
              return false;
            }
          }
        }
      }
      return true;
      }

      isWinnerf(i: string[], idx: number, j: number): boolean {
        // console.log('i: ', i, this.fWin[idx]);
        
        if (i[+j] == this.fWin[idx]) {
          return true;
        }
        return false;
      }

      isWinners(i: string[], idx: number, j: number): boolean {
        
        if (i[+j] == this.sWin[idx]) {
          return true;
        }
        return false;
      }

      isWinnerq(i: string[], idx: number, j: number): boolean {
        
        if (i[+j] == this.qWin[idx]) {
          return true;
        }
        return false;
      }

      toEtherscan() {
        const url = 'https://sepolia.etherscan.io/' + 'tx/' + this.global.hash_tx;
        window.open(url, "_blank");
      }

      blockchainData: boolean = false;
      blockchainDataReq() {
        this.http.get(
          getBaseUrl() + '/api/blockchain/tournament/' + '?tid=' + this.global.tournamentID,
            {
              headers: { Authorization: 'Bearer ' + localStorage.getItem('token') },
              withCredentials: true,
              //headers: {Authorization: 'Bearer ' + this.global.user.getToken()}
            })
            .subscribe((data: any) => {
              if(data.data.error == 'true') {
                //console.log(data);
                alert('wait block validation');
              } else if (data.data) {
                //console.log(data);
                this.quarterArray = data.data.structure.quarters
                this.semiArray = data.data.structure.semifinals;
                this.finalArray = data.data.structure.finals;
                this.qWin = data.data.winners.quarters;
                this.sWin = data.data.winners.semifinals;
                this.fWin = data.data.winners.finals;
                // //console.log(this.quarterArray);
                // //console.log(this.semiArray);
                // //console.log(this.finalArray);
                // //console.log(this.qWin);
                // //console.log(this.sWin);
                // //console.log(this.fWin);
                const b_id_winner = document.getElementById('id-winner');
                if (b_id_winner) {
                  b_id_winner.textContent = '#' + this.fWin[1];
                }
                this.blockchainData = true;
              } else {
                //console.log('Indexing, wait please...');
              }
      }), (error: any) => {
        //console.log('Error', error);
      } 
    }
}

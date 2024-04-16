// angular imports
import { Component } from '@angular/core';
import { FormGroup, FormControl } from '@angular/forms';
// service
import { LanguageService } from '../../service/language.service';
import { FriendService } from 'src/app/service/friend.service';
import { AudioService } from 'src/app/service/audio.service';
import { WebsocketService } from 'src/app/service/websocket.service';
import { UpdateService } from 'src/app/service/update.service';
// other
import { SidePanelComponent } from '../side-panel/side-panel.component';
import { Global } from 'src/app/shared/global';

@Component({
  selector: 'app-add-friend',
  templateUrl: './add-friend.component.html',
  styleUrls: ['./add-friend.component.css'],
})
export class AddFriendComponent {
  // HTML variables
  addFriendHtml: string = 'Add friend';
  nickPlaceholder: string = 'Write nickname';
  search: string = 'Search';
  add: string = 'Add';
  back: string = 'Back';
  userMap: Map<string, string> = new Map<string, string>();
  errorServer: boolean = false;
  serverErrorText: string = 'Server error';

  // User variables
  language = this.global.user.getLanguage() ?? 'en';
  userList: string[] = [];

  addFriendForm = new FormGroup({
    searchUser: new FormControl(''),
  });

  constructor(
    private languageService: LanguageService,
    private friendService: FriendService,
    private sidePanelComponent: SidePanelComponent,
    private global: Global,
    private audioService: AudioService,
    private websocketService: WebsocketService,
    private updateService: UpdateService
  ) {}

  ngOnInit(): void {
    // //console.log('user online', this.global.onlineUsers);
    //get language
    this.updateLocalizedStrings();

    this.userMap = this.global.userMap;
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[this.global.user.getLanguage() ?? 'en'];
      const keysToUpdate = [
        'addFriendHtml',
        'nickPlaceholder',
        'search',
        'add',
        'back',
        'serverErrorText',
      ];
      for (let key of keysToUpdate) {
        if (langData.hasOwnProperty(key)) {
          this[key] = langData[key];
        }
      }
    });
  }

  searchUser(): void {
    // Play audio
    this.audioService.playAudio(this.audioService.clickButton);

    let nick = this.getEnterValues().nickNew ?? '';
    if (nick.trim() === '') {
      this.userList = [];
      return;
    } else {
      nick = nick.replace(/\s/g, '');
    }
    //console.log('searchUser: ' + nick);
    this.userList = [];
    this.userMap.forEach((value, id) => {
      let toPush = value + '#' + id;
      let toSearch = value.toLowerCase() + '#' + id;
      if (
        toSearch.includes(nick.toLowerCase()) &&
        id !== this.global.user.getId().toString() &&
        !this.global.user.getFriendList().includes(Number(id)) &&
        !this.sidePanelComponent.postFriendRequest.some(
          (request) => request.id == id
        ) &&
        !this.sidePanelComponent.getFriendRequest.some(
          (request) => request.id == id
        )
      ) {
        this.userList.push(toPush);
      }
    });
    return;
  }

  getEnterValues() {
    const nickValue = this.addFriendForm.get('searchUser')?.value;
    //console.log('Entered nickname: ' + nickValue);
    return { nickNew: nickValue };
  }

  addFriendClicked(user: string) {
    // Play audio
    this.audioService.playAudio(this.audioService.clickButton);

    //console.log('add friend clicked ' + user);
    let id = Number(user.split('#')[1]);
    //console.log('id: ' + id);
    this.friendService.addFriend(id).subscribe((data) => {
      //console.log('addFriend: ', data);
      this.websocketService.sendFriendRequest(id);
      this.sidePanelComponent.postFriendRequest.push({
        id: id.toString(),
        nick: this.userMap.get(user.toString()) ?? '',
      });
      this.searchUser();
    });
  }

  closeAddFriend() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.updateService.triggerUpdate();
    this.sidePanelComponent.isAddFriendOpen = false;
  }
}

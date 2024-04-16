// Angular imports
import { Component } from '@angular/core';
// Service
import { LanguageService } from 'src/app/service/language.service';
import { WebsocketService } from 'src/app/service/websocket.service';
import { FriendService } from 'src/app/service/friend.service';
// Other
import { Global } from 'src/app/shared/global';

@Component({
  selector: 'app-panel-side',
  templateUrl: './panel-side.component.html',
  styleUrls: ['./panel-side.component.css'],
})
export class PanelSideComponent {
  // Variables in html
  emptyFriend: string = 'No friends :(';
  friends: string = 'Friends';

  // User variables
  language = this.global.user.getLanguage() ?? 'en';
  profilePic = this.global.user.getAvatar() ?? '';
  nickName = this.global.user.getNickname() ?? 'User';
  idNick = this.global.user.getId().toString() ?? '0';
  friendListArray: Array<{ id: string; nick: string; isOnline: boolean }> = [];

  constructor(
    private global: Global,
    private languageService: LanguageService,
    private websocketService: WebsocketService,
    private friendService: FriendService
  ) {}

  ngOnInit(): void {
    // Update language and user data
    this.updateLocalizedStrings();
    this.updateData();
    this.updateFriend();

    this.websocketService.getActiveUsers().subscribe((data) => {
      this.global.getUsers();
      let jsonData = data;

      switch (jsonData.action) {
        case 'join_leave':
          if (
            this.global.user.getFriendList().includes(jsonData.event_user_id)
          ) {
            this.updateFriend();
          }
          break;
        case 'change_name':
          this.global.userMap.set(jsonData.id.toString(), jsonData.name);
          if (this.checkFriendList(jsonData) === true) {
            this.updateFriend();
          }
          break;
        case 'player_deleted':
          if (this.checkFriendList(jsonData) === true) {
            this.updateFriend();
          }
          break;
        case 'friend_deleted':
        case 'friend_added':
          if (this.global.user.getId() === jsonData.player_id) {
            this.updateFriend();
          }
          break;
      }
    });
  }

  checkFriendList(jsonData: any) {
    const ids = [...this.friendListArray.map((friend) => friend.id)];
    if (
      ids.includes(jsonData.player_id) ||
      ids.includes(jsonData.event_user_id) ||
      ids.includes(jsonData.id)
    ) {
      return true;
    }
    return false;
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[this.global.user.getLanguage() ?? 'en'];
      const keysToUpdate = [
        'addFriendHtml',
        'friends',
        'friendsRequests',
        'settings',
        'logout',
        'emptyFriend',
        'emptyFriendRequest',
      ];
      for (let key of keysToUpdate) {
        if (langData.hasOwnProperty(key)) {
          this[key] = langData[key];
        }
      }
    });
  }

  updateData() {
    this.nickName = this.global.user.getNickname() ?? 'User';
    this.idNick = this.global.user.getId().toString() ?? '0';
    this.profilePic = this.global.user.getAvatar() ?? '';
    this.language = this.global.user.getLanguage() ?? 'en';
  }

  openedF = false;
  getFriendList() {
    if (this.openedF) {
      return;
    }
    this.openedF = true;
    this.updateFriend();
    setTimeout(() => {
      this.openedF = false;
    }, 5000);
  }

  // Function to handle friend list data
  handleFriendListData(data: any) {
    let friendList = JSON.parse(data.data.friend_list);
    this.global.user.cleanFriendList();
    let onlineFriend: Array<{ id: string; nick: string; isOnline: boolean }> =
      [];
    let offlineFriend: Array<{ id: string; nick: string; isOnline: boolean }> =
      [];

    friendList.forEach((element: any) => {
      this.global.user.addFriend(element);
      if (
        this.global.onlineUsers.active_users &&
        this.global.onlineUsers.active_users.includes(Number(element))
      ) {
        onlineFriend.push({
          id: element,
          nick: this.global.userMap.get(element.toString()) ?? '',
          isOnline: true,
        });
      } else {
        offlineFriend.push({
          id: element,
          nick: this.global.userMap.get(element.toString()) ?? '',
          isOnline: false,
        });
      }
    });

    onlineFriend = this.sortFriends(onlineFriend);
    offlineFriend = this.sortFriends(offlineFriend);
    this.friendListArray = onlineFriend.concat(offlineFriend);
  }

  // Function to sort friends
  sortFriends(friends: Array<{ id: string; nick: string; isOnline: boolean }>) {
    return friends.sort((a, b) => {
      if (a.nick === b.nick) {
        return Number(a.id) - Number(b.id);
      }
      return a.nick.localeCompare(b.nick);
    });
  }

  // Updated function
  updateFriend() {
    this.friendListArray = [];
    this.friendService.getUserID(this.global.user.getId()).subscribe((data) => {
      if (data.error) {
        return;
      }
      this.handleFriendListData(data);
    });
  }
}

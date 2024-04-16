// angular imports
import { Component } from '@angular/core';
import { Router } from '@angular/router';
// service
import { UpdateService } from 'src/app/service/update.service';
import { LanguageService } from 'src/app/service/language.service';
import { FriendService } from 'src/app/service/friend.service';
import { AudioService } from 'src/app/service/audio.service';
import { WebsocketService } from 'src/app/service/websocket.service';
// other
import { Global } from 'src/app/shared/global';

export enum ProfileType {
  UPROFILE = 0,
  FRIEND = 1,
  FRIENDREQ = 2,
}

@Component({
  selector: 'app-side-panel',
  templateUrl: './side-panel.component.html',
  styleUrls: ['./side-panel.component.css'],
})
export class SidePanelComponent {
  // Variables in html
  addFriendHtml: string = 'Add Friend';
  friends: string = 'Friends';
  friendsRequests: string = 'Friends Requests';
  settings: string = 'Settings';
  logout: string = 'Logout';
  emptyFriend: string = 'No friends :(';
  emptyFriendRequest: string = 'No requests';

  // User variables
  language = this.global.user.getLanguage() ?? 'en';
  nickName = this.global.user.getNickname() ?? 'User';
  idNick = this.global.user.getId().toString() ?? '0';
  profilePic = this.global.user.getAvatar() ?? '';
  postFriendRequest: Array<{ id: string; nick: string }> = [];
  getFriendRequest: Array<{ id: string; nick: string }> = [];
  friendListArray: Array<{ id: string; nick: string; isOnline: boolean }> = [];

  ProfileType = ProfileType;

  constructor(
    private languageService: LanguageService,
    private global: Global,
    private updateService: UpdateService,
    private router: Router,
    private friendService: FriendService,
    private audioService: AudioService,
    private websocketService: WebsocketService
  ) {}

  ngOnInit(): void {
    // Update language and user data
    this.updateService.updateNeeded$.subscribe(() => {
      // //console.log('SidePanelComponent: updateNeeded$');
      this.updateLocalizedStrings();
      this.updateData();
      this.updateFriend();
      this.updatePendingFriend();
    });

    this.websocketService.getActiveUsers().subscribe((data) => {
      this.global.getUsers();
      // //console.log('Active-getActiveUsers SidePannel: ', data);
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
          // //console.log('enter change_name');
          this.global.userMap.set(jsonData.id.toString(), jsonData.name);
          if (this.checkFriendList(jsonData) === true) {
            this.updateFriend();
            this.updatePendingFriend();
          }
          break;
        case 'player_deleted':
          if (this.checkFriendList(jsonData) === true) {
            // //console.log('enter player_deleted');
            this.updateFriend();
          }
          break;
        case 'friend_deleted':
        case 'friend_added':
          if (this.global.user.getId() === jsonData.player_id) {
            // //console.log('enter friend_deleted or friend_added');
            this.updateFriend();
          }
          break;
        case 'new_friend_request':
          if (this.global.user.getId() === jsonData.player_id) {
            // //console.log('enter new_friend_request');
            this.updatePendingFriend();
          }
          break;
      }
    });
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

  checkFriendList(jsonData: any) {
    const ids = [
      ...this.friendListArray.map((friend) => friend.id),
      ...this.postFriendRequest.map((friend) => friend.id),
      ...this.getFriendRequest.map((friend) => friend.id),
    ];
    if (
      ids.includes(jsonData.player_id) ||
      ids.includes(jsonData.event_user_id) ||
      ids.includes(jsonData.id)
    ) {
      return true;
    }
    return false;
  }

  // Update user data
  updateData() {
    this.nickName = this.global.user.getNickname() ?? 'User';
    this.idNick = this.global.user.getId().toString() ?? '0';
    this.profilePic = this.global.user.getAvatar() ?? '';
    this.language = this.global.user.getLanguage() ?? 'en';
  }

  // -----------------Friend Stuff--------------------

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
    // //console.log('FriendListArray: ', this.friendListArray);
  }

  openedPR = false;
  getPendingRequest() {
    if (this.openedPR) {
      return;
    }
    this.openedPR = true;
    this.updatePendingFriend();
    setTimeout(() => {
      this.openedPR = false;
    }, 5000);
  }

  sortFriends2(friends: Array<{ id: string; nick: string }>) {
    return friends.sort((a, b) => {
      if (a.nick === b.nick) {
        return Number(a.id) - Number(b.id);
      }
      return a.nick.localeCompare(b.nick);
    });
  }

  updatePendingFriend() {
    // Get friend pending requests
    this.friendService.getFriendsPending().subscribe((data) => {
      this.postFriendRequest = [];
      this.getFriendRequest = [];
      if (
        data.data.length == 0 ||
        data.data == null ||
        !Array.isArray(data.data)
      ) {
        return;
      }
      data.data.forEach((element: any) => {
        if (element.creator == this.global.user.getId()) {
          this.postFriendRequest.push({
            id: element.receiver,
            nick: this.global.userMap.get(element.receiver.toString()) ?? '',
          });
        } else {
          this.getFriendRequest.push({
            id: element.creator,
            nick: this.global.userMap.get(element.creator.toString()) ?? '',
          });
        }
      });
      this.getFriendRequest = this.sortFriends2(this.getFriendRequest);
    });
  }

  // -------------------------------------------

  isSettingsOpen = false;
  openSettings() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.isSettingsOpen = true;
  }

  isAddFriendOpen = false;
  openAddFriend() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.isAddFriendOpen = true;
  }

  isFriendListOpen = false;
  openFriendList() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.isFriendListOpen = true;
  }

  closeFriendList() {
    this.isFriendListOpen = false;
  }

  isProfileOpen = false;
  isUser = false;
  isFriend = false;
  isFriendReq = false;
  user = this.nickName + '#' + this.idNick;
  userProfile: string = '';
  openProfile(id: string, type: number) {
    this.isProfileOpen = true;
    this.userProfile = id;
    this.isUser = false;
    this.isFriend = false;
    this.isFriendReq = false;
    if (type == ProfileType.UPROFILE) {
      this.isUser = true;
    } else if (type == ProfileType.FRIEND) {
      this.isFriend = true;
    } else if (type == ProfileType.FRIENDREQ) {
      this.isFriendReq = true;
    }
  }

  logOut() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.global.isLogged = false;
    this.global.user.clear();
    localStorage.removeItem('token');
    this.websocketService.closeActiveUsersWebSocket();
    this.websocketService.resetTournamentSocket();
    this.router.navigate(['/']);
  }
}

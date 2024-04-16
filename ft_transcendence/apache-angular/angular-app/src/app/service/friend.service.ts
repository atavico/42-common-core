import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { getBaseUrl } from '../shared/generic';

@Injectable({
  providedIn: 'root',
})
export class FriendService {
  constructor(private http: HttpClient,
    ) {}

  // Get list of registered users
  getAllUsers() {
    return this.http.get<any>(
      getBaseUrl() + '/api/users/player_names/',
      {
        headers: { Authorization: 'Bearer ' + localStorage.getItem('token') },
        withCredentials: true,
        //headers: {Authorization: 'Bearer ' + this.global.user.getToken()}
      }
    );
  }

  // Add friend to user list
  addFriend(id: number) {
    //console.log('addFriend: ', id);
    return this.http.post<JSON>(
      getBaseUrl() + '/api/users/add_friend/',
      {
        receiver_id: id,
      },
      {
        headers: { Authorization: 'Bearer ' + localStorage.getItem('token') },
        responseType: 'text' as 'json',
        withCredentials: true,
      }
    );
  }

  // Add or Reject friend request
  friendStatus(creator: number, receiver: number, status: string) {
    //console.log(
    //   'receiver: ' + receiver,
    //   'creator: ' + creator,
    //   'status: ' + status
    // );
    return this.http.put<any>(
      getBaseUrl() + '/api/users/friend_validate/',
      {
        receiver: receiver,
        creator: creator,
        status: status,
      },
      {
        headers: { Authorization: 'Bearer ' + localStorage.getItem('token') },
        // responseType: 'text' as 'json',
        // withCredentials: true,
      }
    );
  }

  // Get my friends
  getFriends() {
    return this.http.get<any>(
      getBaseUrl() + '/api/users/friends/'
      , {
      headers: { Authorization: 'Bearer ' + localStorage.getItem('token') },
    });
  }

  // Get list of pending friends
  getFriendsPending() {
    return this.http.get<any>(
      getBaseUrl() + '/api/users/get_pending_friends/',
      {
        headers: { Authorization: 'Bearer ' + localStorage.getItem('token') },
      }
    );
  }

  // Get specific user by id
  getUserID(id: number) {
    return this.http.get<any>(
      getBaseUrl() + '/api/users/player/' + id,
      {
      headers: { Authorization: 'Bearer ' + localStorage.getItem('token') },
    });
  }

  // Get user games played 1v1
  getGamesPlayed1(id: number) {
    if (Number.isNaN(id))
      return;
    return this.http.get<any>(
      getBaseUrl() + '/api/tournaments/match_history/' + id,
      {
        headers: {
          Authorization: 'Bearer ' + localStorage.getItem('token'),
        },
      }
    );
  }

  // Get user games played Tournament
  getGamesPlayedT(id: number) {
    return this.http.get<any>(
      getBaseUrl() + '/api/tournaments/history/' + id,
      {
        headers: {
          Authorization: 'Bearer ' + localStorage.getItem('token'),
        },
      }
    );
  }

  // Delete friend
  deleteFriend(id: number) {
    return this.http.put<any>(
      getBaseUrl() + '/api/users/remove_friend/',
      {
        friend_id: id,
      },
      {
        headers: { Authorization: 'Bearer ' + localStorage.getItem('token') },
      }
    );
  }
}

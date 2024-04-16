import { Injectable } from '@angular/core';
import { BehaviorSubject } from 'rxjs';
import { HttpClient } from '@angular/common/http';
import { getBaseUrl } from '../shared/generic';

@Injectable({
  providedIn: 'root',
})
export class UpdateService {
  constructor(private http: HttpClient) {}

  private updateNeeded = new BehaviorSubject<boolean>(false);
  updateNeeded$ = this.updateNeeded.asObservable();
  triggerUpdate() {
    this.updateNeeded.next(true);
  }

  updateSettings(nick: string, lang: string, pic: string) {
    //console.log('updateSettings nickname: ' + nick);
    //console.log('updateSettings language: ' + lang);
    //console.log('updateSettings profile picture: ' + pic);
    return this.http.put<any>(
      getBaseUrl() + '/api/users/player/',
      {
        username: nick,
        language: lang,
        avatar: pic, // base64
      },
      {
        headers: {
          Authorization: 'Bearer ' + localStorage.getItem('token'),
        },
      }
    );
  }

  deleteUser() {
    return this.http.delete<any>(
      getBaseUrl() + '/api/users/player_delete/',
      {
        headers: {
          Authorization: 'Bearer ' + localStorage.getItem('token'),
        },
      }
    );
  }
}

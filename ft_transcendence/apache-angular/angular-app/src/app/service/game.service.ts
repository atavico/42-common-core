import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { HttpHeaders } from '@angular/common/http';
import { getBaseUrl } from '../shared/generic';

@Injectable({
  providedIn: 'root',
})
export class GameService {
  constructor(private http: HttpClient) {}

  getMatches() {
    // //console.log('getMatches');
    return this.http.get(getBaseUrl() + '/api/tournaments/', {
      headers: new HttpHeaders({
        Authorization: 'Bearer ' + localStorage.getItem('token'),
      }),
    });
  }

  createMatch(body: any) {
    return this.http.post(getBaseUrl() + '/api/tournaments/', body, {
      headers: new HttpHeaders({
        Authorization: 'Bearer ' + localStorage.getItem('token'),
        // 'withCredentials': 'true',
        // 'responseType': 'json',
        // 'referrel': 'https://localhost:4343'
      }),
    });
  }

  postLocalMatch(body: any) {
    return this.http.post(getBaseUrl() + '/api/local_history/matches/', body, {
      headers: new HttpHeaders({
        Authorization: 'Bearer ' + localStorage.getItem('token'),
      }),
    });
  }

  getLocalMatches(id: number) {
    return this.http.get(getBaseUrl() + '/api/local_history/matches/' + id, {
      headers: new HttpHeaders({
        Authorization: 'Bearer ' + localStorage.getItem('token'),
      }),
    });
  }
}

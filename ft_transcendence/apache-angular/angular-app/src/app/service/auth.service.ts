import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { getBaseUrl } from '../shared/generic';

@Injectable({
  providedIn: 'root',
})
export class AuthService {
  //isLogged: boolean = false;

  constructor(
    private http: HttpClient,
    ) {}

  signUp(email: string | undefined | null, password1: string | undefined | null,  password2: string | undefined | null) {
    return this.http.post<JSON>(
      getBaseUrl() + '/users/register/',
      {
        email: email,
        password1: password1,
        password2: password2
      },
      { 
        withCredentials: true, 
        responseType: 'text' as 'json'
      }
    );
  }

  logIn(email: string | null | undefined, password: string | null | undefined) {
    //console.log("[INFO  ]: ", email);
    return this.http.post<JSON>(
      getBaseUrl() + '/users/login/',
      {
        email: email,
        password: password
      },
      { 
        withCredentials: true,
        responseType: 'text' as 'json' }
    );
  }

  sendCode(code: string | null | undefined) {
    // //console.log("[INFO  ]: ", code);
    return this.http.post<JSON>(
      getBaseUrl() + '/oauth/',
      {
        code: code,
        credentials: 'include',
      },
      {
        responseType: 'text' as 'json',
      }
    );
  }

  checkAuth(): boolean {
    //rivedere
    if (localStorage.getItem('token') !== null) {
      //console.log("checkAuthToken: ", localStorage.getItem('token'));
      return  true;
    }
    return false;
  }

  getUserFromJwt(localToken: string | null | undefined) {
    return this.http.get<any>(
      getBaseUrl() + '/users/session/',
      {
        headers: new HttpHeaders({
          'Authorization': 'Bearer ' + localToken
        }),
      }
    );
  }
}

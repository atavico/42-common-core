// angular imports
import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { throwError } from 'rxjs';
import { catchError } from 'rxjs/operators';
//service
import { LanguageService } from '../service/language.service';
import { AuthService } from '../service/auth.service';
import { AudioService } from '../service/audio.service';
import { WebsocketService } from '../service/websocket.service';
// other
import { Global } from '../shared/global';
import { environment } from '../../environments/environment';

@Component({
  selector: 'app-access-filter',
  templateUrl: './access-filter.component.html',
})
export class AccessFilterComponent implements OnInit {
  // Variables in html
  login42: string = 'Login with 42';
  signUp: string = 'Sign Up';
  login: string = 'Login';
  loading: boolean = false;
  loadingStr: string = 'Loading...';
  ip: string = environment.IP_ADDRESS;

  // User variables
  language = localStorage.getItem('language') || 'en';

  constructor(
    private languageService: LanguageService,
    private global: Global,
    private activatedRoute: ActivatedRoute,
    private authService: AuthService,
    private router: Router,
    private audioService: AudioService,
    private websocketService: WebsocketService
  ) {}

  ngOnInit(): void {
    if (!localStorage.getItem('language'))
      localStorage.setItem('language', 'en');
    // Get language from json and set variables
    this.updateLocalizedStrings();

    const actSession = this.authService.checkAuth();
    if (actSession) {
      //console.log('session is active');
      const localToken = localStorage.getItem('token');
      //console.log('localToken: ', localToken);
      this.global.isLogged = true;
      //prendi errore
      this.authService
        .getUserFromJwt(localToken)
        .pipe(
          catchError((error: any) => {
            //console.log('error: ', error);
            this.global.isLogged = false;
            localStorage.removeItem('token');
            this.router.navigate(['']);
            return throwError(() => error);
          })
        )
        .subscribe((data: any) => {
          //console.log('getUserFromJwt: ', data);
          this.global.user.setUser(data.data);
          this.global.isLogged = true;
          this.websocketService.reinitializeOnlineFriendSocket();
          this.websocketService.getActiveUsers().subscribe((data) => {
            let jsonData = data;
            if (jsonData.action === 'join_leave') {
              // //console.log('AccessFilter-getActiveUsers: ', data);
              this.global.onlineUsers = jsonData;
              // //console.log('AccessFilter-global-onlineUsers: ', this.global.onlineUsers);
            }
          });
          //console.log('localToken: ', localStorage.getItem('token'));
          this.router.navigate(['/main-menu']);
        });
    } else {
      //console.log('session is not active');
      this.activatedRoute.queryParams.subscribe((params: any) => {
        if (params.code) {
          this.loading = true;
          //console.log("Requested 42 retrieved code -> ", params.code)
          this.authService.sendCode(params.code).subscribe((data: any) => {
            //console.log('dataRet: ', data);
            const responseParsed = JSON.parse(data);
            this.global.user.setUser(responseParsed.data);
            localStorage.setItem('token', responseParsed.data.Token);
            this.websocketService.reinitializeOnlineFriendSocket();
            this.websocketService.getActiveUsers().subscribe((data) => {
              let jsonData = data;
              if (jsonData.action === 'join_leave') {
                // //console.log('AccessFilter-getActiveUsers: ', data);
                this.global.onlineUsers = jsonData;
                // //console.log('AccessFilter-global-onlineUsers: ', this.global.onlineUsers);
              }
            });
            //console.log('localToken: ', localStorage.getItem('token'));
            this.global.isLogged = true;
            this.router.navigate(['/main-menu']);
            this.loading = false;
          });
        }
      });
    }
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[localStorage.getItem('language') || 'en'];
      const keysToUpdate = ['login42', 'signUp', 'login', 'loadingStr'];
      for (let key of keysToUpdate) {
        if (langData.hasOwnProperty(key)) {
          this[key] = langData[key];
        }
      }
    });
  }

  loginWithIntra() {
    this.audioService.playAudio(this.audioService.clickButton);
    // const redirectUrl = 'http://localhost:4343';
    // const clientId =
    //   'u-s4t2ud-18f32d4b5639598cdacde505bfa8cb97208103c99895803c2ac65f6e180b4f6f';
    // window.location.href = `https://api.intra.42.fr/oauth/authorize?client_id=${clientId}&redirect_uri=${redirectUrl}&response_type=code`;
  }

  clickSignup() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.router.navigate(['/sign-up']);
  }

  clickLogin() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.router.navigate(['/log-in']);
  }
}

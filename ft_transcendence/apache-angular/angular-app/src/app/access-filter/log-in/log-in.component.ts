// angular imports
import { Component } from '@angular/core';
import { FormGroup, FormControl } from '@angular/forms';
import { Router } from '@angular/router';
import { catchError, throwError, Observable } from 'rxjs';
// service
import { LanguageService } from '../../service/language.service';
import { AuthService } from '../../service/auth.service';
import { AudioService } from '../../service/audio.service';
import { WebsocketService } from '../../service/websocket.service';
// other
import { Global } from '../../shared/global';

@Component({
  selector: 'app-log-in',
  templateUrl: './log-in.component.html',
})
export class LogInComponent {
  // Variables in html
  back: string = 'Back';
  loginform: string = 'Login Form';
  insertEmail: string = 'Insert email';
  insertPassword: string = 'Insert password';
  login: string = 'Login';
  emailPasswordError: string = 'Email or password is wrong';
  serverErrorText: string = 'Server error';
  serverMsgText: string = 'Server error: ';
  errorMsg: string = 'Server error: ';

  // User variables
  language = this.global.user.getLanguage() ?? 'en';

  loginForm = new FormGroup({
    email: new FormControl(''),
    password: new FormControl(''),
  });

  constructor(
    private languageService: LanguageService,
    private authService: AuthService,
    private global: Global,
    private router: Router,
    private audioService: AudioService,
    private websocketService: WebsocketService
  ) {}

  ngOnInit(): void {
    // Get language from json and set variables
    this.updateLocalizedStrings();
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[localStorage.getItem('language') || 'en'];
      const keysToUpdate = [
        'back',
        'loginform',
        'insertEmail',
        'insertPassword',
        'login',
        'emailPasswordError',
        'serverErrorText',
        'serverMsgText',
      ];
      for (let key of keysToUpdate) {
        if (langData.hasOwnProperty(key)) {
          this[key] = langData[key];
        }
      }
    });
  }

  // Get entered values
  getEnterValues() {
    return {
      email: this.loginForm.get('email')?.value,
      pass: this.loginForm.get('password')?.value,
    };
  }

  // Basic Email validation
  checkEmail(email: string): boolean {
    let emailRegEx = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;
    return emailRegEx.test(email);
  }

  // Basic Password validation
  checkPassword(password: string): boolean {
    let passwordRegEx =
      /^(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])(?=.*[~`!@#$%^&*()_\-+={[}\]|:;"'<,>.?/])[A-Za-z0-9~`!@#$%^&*()_\-+={[}\]|:;"'<,>.?/]{8,}$/;
    return passwordRegEx.test(password);
  }

  loginError = false;
  serverError = false;
  serverMsg = false;
  onLogin() {
    // Play audio
    this.audioService.playAudio(this.audioService.clickButton);
    // Reset error message
    this.loginError = false;
    this.serverError = false;
    this.serverMsg = false;

    // Get entered values
    const { email, pass } = this.getEnterValues();

    // Check if email or password is missing
    if (!email && !pass) return;
    if (!email || !pass) {
      this.loginError = true;
      return;
    }

    // Check if email and password is valid
    if (!this.checkEmail(email) || !this.checkPassword(pass)) {
      this.loginError = true;
      return;
    }
    if (email !== '' && pass !== '') {
      this.authService
        .logIn(email, pass)
        .pipe(
          catchError((error: any): Observable<never> => {
            try {
              //console.error('Error logging in: ', error);
              let errorJson = JSON.parse(error.error).data;
              // //console.log("errorJson: ", errorJson);
              let errorMessage = errorJson.message;
              // //console.log("errorMessage: ", errorMessage);
              this.errorMsg = errorMessage;
              this.serverMsg = true;
            } catch (e) {
              this.serverError = true;
            }
            return throwError(() => error);
          })
        )
        .subscribe((data: any) => {
          // //console.log('logIn: ', data);
          this.global.isLogged = true;

          const responseParsed = JSON.parse(data);
          this.global.user.setUserByLogin(data);
          localStorage.setItem('token', responseParsed.token);
          this.websocketService.reinitializeOnlineFriendSocket();
          this.websocketService.getActiveUsers().subscribe((data) => {
            let jsonData = data;
            if (jsonData.action === 'join_leave') {
              // //console.log('Login-getActiveUsers: ', data);
              this.global.onlineUsers = jsonData;
              // //console.log('Login-global-onlineUsers: ', this.global.onlineUsers);
            }
          });
          this.checkTokenAndNavigate();
        });
    }
  }

  // Check if token is set and navigate to main-menu
  checkTokenAndNavigate() {
    const token = localStorage.getItem('token');
    //console.log('localToken: ', token);

    if (token) {
      this.router.navigate(['/main-menu']);
    } else {
      setTimeout(() => this.checkTokenAndNavigate(), 500);
    }
  }

  clickBack() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.router.navigate(['/']);
  }
}

// angular imports
import { Component } from '@angular/core';
import { FormGroup, FormControl } from '@angular/forms';
import { Router } from '@angular/router';
import { catchError } from 'rxjs/operators';
import { throwError, Observable } from 'rxjs';
// service
import { LanguageService } from '../../service/language.service';
import { AuthService } from '../../service/auth.service';
import { AudioService } from '../../service/audio.service';
import { WebsocketService } from 'src/app/service/websocket.service';
import { UpdateService } from 'src/app/service/update.service';
// other
import { Global } from '../../shared/global';

@Component({
  selector: 'app-sign-up',
  templateUrl: './sign-up.component.html',
})
export class SignUpComponent {
  // Variables in html
  back: string = 'Back';
  signupform: string = 'SignUp Form';
  insertEmail: string = 'Insert email';
  insertPassword: string = 'Insert password';
  signUp: string = 'Sign up';
  passwordRule1: string = 'Password rules';
  passwordRule2: string = '- 8 characters';
  passwordRule3: string = '- 1 uppercase letter';
  passwordRule4: string = '- 1 lowercase letter';
  passwordRule5: string = '- 1 number';
  passwordRule6: string = '- 1 special character';
  emailMissing: string = 'Email is missing';
  passwordMissing: string = 'Password is missing';
  emailWrong: string = 'Email is wrong';
  passwordWrong: string = 'Password is wrong';
  serverErrorText: string = 'Server error';
  serverMsgText: string = 'Server error: ';
  errorMsg: string = 'Error';

  // User variables
  language = localStorage.getItem('language') || 'en';

  signupForm = new FormGroup({
    email: new FormControl(''),
    password: new FormControl(''),
  });

  constructor(
    private languageService: LanguageService,
    private authService: AuthService,
    private global: Global,
    private router: Router,
    private audioService: AudioService,
    private websocketService: WebsocketService,
    private updateService: UpdateService
  ) {}

  ngOnInit(): void {
    // Get JSON and update localized strings
    this.updateLocalizedStrings();
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[localStorage.getItem('language') || 'en'];
      const keysToUpdate = [
        'back',
        'signupform',
        'insertEmail',
        'insertPassword',
        'signUp',
        'passwordRule1',
        'passwordRule2',
        'passwordRule3',
        'passwordRule4',
        'passwordRule5',
        'passwordRule6',
        'emailMissing',
        'passwordMissing',
        'emailWrong',
        'passwordWrong',
        'serverErrorText',
        'serverMsgText',
        'errorMsg',
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
      email: this.signupForm.get('email')?.value,
      password: this.signupForm.get('password')?.value,
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

  // Bool for error messages
  errors = {
    email: false,
    emailMissing: false,
    password: false,
    passwordMissing: false,
    serverError: false,
    serverMsg: false,
  };

  onSignUp() {
    // Play audio
    this.audioService.playAudio(this.audioService.clickButton);
    // Reset error messages
    this.errors = {
      email: false,
      emailMissing: false,
      password: false,
      passwordMissing: false,
      serverError: false,
      serverMsg: false,
    };

    // Get entered values
    const { email, password } = this.getEnterValues();

    // Check if email and password is missing
    if (!email && !password) return;
    this.errors.emailMissing = !email;
    this.errors.passwordMissing = !password;

    // Check if email and password is valid
    this.errors.email = Boolean(email) && !this.checkEmail(email ?? '');
    this.errors.password =
      Boolean(password) && !this.checkPassword(password ?? '');

    if (Object.values(this.errors).every((error) => !error)) {
      // //console.log('\nemail: ' + email + '\npassword: ' + password);
      this.authService
        .signUp(email, password, password)
        .pipe(
          catchError((error: any): Observable<never> => {
            try {
              //console.error('There was an error during sign up: ', error);
              let errorMessage = JSON.parse(error.error).data;
              // //console.log('errorMessage: ', errorMessage);
              let emailError = JSON.parse(errorMessage).email;
              // //console.log('emailError: ', emailError[0].message);
              this.errorMsg = emailError[0].message;
              this.errors.serverMsg = true;
            } catch (e) {
              this.errors.serverError = true;
            }
            return throwError(() => error);
          })
        )
        .subscribe((data: any) => {
          this.global.isLogged = true;

          const responseParsed = JSON.parse(data);
          this.global.user.setUserBySignup(data);
          localStorage.setItem('token', responseParsed.data.Token);
          this.websocketService.reinitializeOnlineFriendSocket();
          this.websocketService.getActiveUsers().subscribe((data) => {
            let jsonData = data;
            if (jsonData.action === 'join_leave') {
              // //console.log('SignUp-getActiveUsers: ', data);
              this.global.onlineUsers = jsonData;
              // //console.log('SignUp-global-onlineUsers: ', this.global.onlineUsers);
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

    if (token && this.global.user.getAvatar() != "") {
      this.updateService
        .updateSettings(
          this.global.user.getNickname(),
          this.global.user.getLanguage(),
          this.global.user.getAvatar()
        )
        .subscribe(() => {
          this.router.navigate(['/main-menu']);
        });
    } else {
      setTimeout(() => this.checkTokenAndNavigate(), 500);
    }
  }

  clickBack() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.router.navigate(['/']);
  }
}

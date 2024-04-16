// angular imports
import { Component, HostListener } from '@angular/core';
import { FormGroup, FormControl } from '@angular/forms';
import { Router } from '@angular/router';
import { HttpErrorResponse } from '@angular/common/http';
import { catchError, throwError } from 'rxjs';
// service
import { UpdateService } from 'src/app/service/update.service';
import { LanguageService } from 'src/app/service/language.service';
import { AudioService } from 'src/app/service/audio.service';
import { WebsocketService } from 'src/app/service/websocket.service';
// other
import { SidePanelComponent } from '../side-panel/side-panel.component';
import { Global } from 'src/app/shared/global';

@Component({
  selector: 'app-settings',
  templateUrl: './settings.component.html',
  styleUrls: ['./settings.component.css'],
})
export class SettingsComponent {
  // HTML variables
  settings: string = 'Settings';
  profilePicture: string = 'Profile picture';
  nickname: string = 'Nickname';
  selectLanguage: string = 'Select language';
  save: string = 'Save';
  deleteAccountStr: string = 'Delete account';
  back: string = 'Back';
  changingTo: string = 'Changing to';
  nickNameErrorMsg1: string = 'Nickname must be between 1 and 8 characters';
  nickNameErrorMsg2: string = 'and contain only letters, numbers and _';
  currentLanguageMsg: string = 'Current language: ';
  deleteAccountQuestion: string = 'Are you sure? Write yes';
  confirm: string = 'Confirm';
  serverErrorText: string = 'Server error';
  imgErrorFormat: string =
    'Invalid image format. Please upload a JPEG or PNG image.';
  imgErrorSize: string =
    'The file is too large. Please upload a file less than 1MB.';

  // User variables
  nickPlaceholder = this.global.user.getNickname() ?? 'User';
  profilePic = this.global.user.getAvatar() ?? '';
  language = this.global.user.getLanguage() ?? 'en';
  newlanguage = this.global.user.getLanguage() ?? 'en';
  newProfilePic: string = '';

  // Form variables
  settingForm = new FormGroup({
    nickNew: new FormControl(''),
  });

  // Constructor
  constructor(
    private languageService: LanguageService,
    private sidePanelComponent: SidePanelComponent,
    private global: Global,
    private updateService: UpdateService,
    private router: Router,
    private audioService: AudioService,
    private websocketService: WebsocketService
  ) {}

  @HostListener('document:keydown', ['$event'])
  handleKeyboardEvent(event: KeyboardEvent) {
    if (event.key === 'Enter') {
      this.saveSettings();
    }
  }

  ngOnInit(): void {
    // Get language from json and set variables
    this.updateLocalizedStrings();
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[this.newlanguage];
      const keysToUpdate = [
        'settings',
        'profilePicture',
        'nickname',
        'selectLanguage',
        'save',
        'deleteAccountStr',
        'back',
        'changingTo',
        'nickNameErrorMsg1',
        'nickNameErrorMsg2',
        'currentLanguageMsg',
        'serverErrorText',
        'deleteAccountQuestion',
        'confirm',
        'imgErrorFormat',
        'imgErrorSize',
      ];
      for (let key of keysToUpdate) {
        if (langData.hasOwnProperty(key)) {
          this[key] = langData[key];
        }
      }
    });
  }

  //  Returns the value of the nickname from the form.
  getEnterValues() {
    return {
      nickNew2: this.settingForm.get('nickNew')?.value,
    };
  }

  errorFormat: boolean = false;
  errorSize: boolean = false;
  changeProfilePic(event: any) {
    this.errorFormat = false;
    this.errorSize = false;

    const file = event.target.files[0];

    // Check if the file is a JPEG or PNG image
    if (!file.type.match('image/jpeg') && !file.type.match('image/png')) {
      this.errorFormat = true;
      //console.log('Invalid image format. Please upload a JPEG or PNG image.');
      return;
    }

    // Check if the file size is less than 1MB
    const maxSize = 1 * 1024 * 1024; // 1MB in bytes
    if (file.size > maxSize) {
      this.errorSize = true;
      //console.log('The file is too large. Please upload a file less than 1MB.');
      return;
    }

    const reader = new FileReader();
    reader.onload = (e) => {
      if (e.target) {
        const img = new Image();
        img.src = e.target.result as string;
        img.onload = () => {
          const canvas = document.createElement('canvas');
          const ctx = canvas.getContext('2d');
          const MAX_WIDTH = 300;
          const MAX_HEIGHT = 300;
          let width = img.width;
          let height = img.height;

          if (width > height) {
            if (width > MAX_WIDTH) {
              height *= MAX_WIDTH / width;
              width = MAX_WIDTH;
            }
          } else {
            if (height > MAX_HEIGHT) {
              width *= MAX_HEIGHT / height;
              height = MAX_HEIGHT;
            }
          }
          if (ctx) {
            canvas.width = width;
            canvas.height = height;
            ctx.drawImage(img, 0, 0, width, height);

            const dataUrl = canvas.toDataURL('image/png');
            this.newProfilePic = dataUrl;
            this.profilePic = dataUrl;
          }
        };
      }
    };

    reader.readAsDataURL(file);
  }

  // Changes the selected language and stores it in multiple variables.
  changeLanguage(lang: string) {
    // //console.log('Change language to ' + lang);
    this.selectLanguage = lang;
    this.newlanguage = lang;
    this.updateLocalizedStrings();
  }

  // Check if nickname is max 8 characters and only contains letters, numbers and _
  checkNickname(nick: string) {
    this.nickNameError = !(nick.length <= 8 && /^[a-zA-Z0-9_]*$/.test(nick));
    return !this.nickNameError;
  }

  //  Updates the user's nickname if the provided nickname is not empty, not null, and valid.
  updateNickname(enteredNick: string) {
    if (
      enteredNick != '' &&
      enteredNick != null &&
      this.checkNickname(enteredNick)
    ) {
      this.global.user.setNickname(enteredNick);
    }
  }

  // Updates the user's language if the new language is not empty, not null, and different from the current language.
  updateLanguage() {
    if (
      this.newlanguage != '' &&
      this.newlanguage != null &&
      this.newlanguage != this.global.user.getLanguage()
    ) {
      //console.log('Change language to UpdateLanguage = ' + this.newlanguage);
      this.global.user.setLanguage(this.newlanguage);
    }
  }

  // Updates the user's profile picture if the new picture is different from the current one.
  updateProfilePic() {
    if (this.profilePic != this.global.user.getAvatar()) {
      this.global.user.setAvatar(this.profilePic);
    }
  }

  // Save settings and update user
  nickNameError: boolean = false;
  serverError: boolean = false;
  saveSettings() {
    // Play audio
    this.audioService.playAudio(this.audioService.clickButton);

    // Reset error message
    this.nickNameError = false;
    this.serverError = false;

    // Get entered nickname
    const enteredNick = this.getEnterValues().nickNew2 ?? '';

    // If no changes were made, return
    if (
      enteredNick == '' &&
      this.newlanguage == this.global.user.getLanguage() &&
      this.profilePic == this.global.user.getAvatar()
    ) {
      return;
    }

    // Update the nickname, language, and profile picture
    this.updateNickname(enteredNick);
    this.updateLanguage();
    this.updateProfilePic();

    // If there is no error with the nickname, update the settings
    if (this.nickNameError == false) {
      this.updateService
        .updateSettings(
          this.global.user.getNickname(),
          this.global.user.getLanguage(),
          this.global.user.getAvatar()
        )
        .pipe(
          catchError((error: HttpErrorResponse) => {
            //console.log('Error: ', error);
            this.serverError = true;
            return throwError(() => error);
          })
        )
        .subscribe((data: any) => {
          //console.log('update settings data: ', data);
          if (
            enteredNick != this.nickPlaceholder &&
            enteredNick != '' &&
            enteredNick != null
          ) {
            this.websocketService.settingUpdate(
              'change_name',
              enteredNick,
              this.global.user.getId()
            );
          }
          this.sidePanelComponent.isSettingsOpen = false;
          localStorage.setItem('language', this.global.user.getLanguage());
          this.updateService.triggerUpdate();
        });
    }
  }
  //------------------------------------------------

  //---------------Delete account-------------------
  deletePrompt: boolean = false;
  deleteConfirmation: string = '';

  deleteAccount() {
    this.deletePrompt = true;
  }

  confirmDelete() {
    // Play audio
    this.audioService.playAudio(this.audioService.clickButton);

    if (
      (this.deleteConfirmation.toLowerCase() === 'yes' &&
        this.language === 'en') ||
      (this.deleteConfirmation.toLowerCase() === 'si' &&
        this.language === 'it') ||
      (this.deleteConfirmation.toLowerCase() === 'tak' &&
        this.language === 'pl')
    ) {
      //console.log('Delete account');
      this.updateService
        .deleteUser()
        .pipe(
          catchError((error: HttpErrorResponse) => {
            //console.log('Error: ', error);
            this.serverError = true;
            return throwError(() => error);
          })
        )
        .subscribe((data: any) => {
          //console.log('delete account data: ', data);
          this.websocketService.settingUpdate(
            'player_deleted',
            this.nickPlaceholder,
            this.global.user.getId()
          );
          this.sidePanelComponent.logOut();
        });
    }
    // this.deletePrompt = false;
    this.deleteConfirmation = '';
  }
  // ----------------------------------------------

  // Close settings panel
  closeSettings() {
    this.audioService.playAudio(this.audioService.clickButton);
    this.sidePanelComponent.isSettingsOpen = false;
  }
}

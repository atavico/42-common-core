import { Component } from '@angular/core';
import { Global } from 'src/app/shared/global';
import { LanguageService } from 'src/app/service/language.service';
import { UpdateService } from 'src/app/service/update.service';


@Component({
  selector: 'app-footer',
  templateUrl: './footer.component.html',
  styleUrls: ['./footer.component.css'],
})
export class FooterComponent {
  //HTML variables
  toYouByStr: string = 'BROUGHT TO YOU BY:';
  tecnologiesStr: string = 'TECHNOLOGIES:';
  elkStr: string = 'log management and monitoring';
  vaultStr: string = 'encrypt and manage passwords';
  modSecStr: string = 'web application firewall';
  featuresStr: string = 'FEATURES:';
  oauthStr: string = 'log-in with 42 Intra';
  remoteStr: string = 'play with your friends online';
  serverSideStr: string = 'games are computed by the server';
  blockStoredStr: string = 'all tournaments results are stored on ethereums blockchain';
  thanksStr: string = 'THANKS FOR PLAYING!';

  constructor(
    private languageService: LanguageService,
    private global: Global,
    private updateService: UpdateService,
  ) {}

  ngOnInit(): void {
    this.updateLocalizedStrings();
    this.updateService.updateNeeded$.subscribe(() => {
      this.updateLocalizedStrings();
    });
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[this.global.user.getLanguage() ?? 'en'];
      const keysToUpdate = [
        'statistics',
        'toYouByStr',
        'tecnologiesStr',
        'elkStr',
        'vaultStr',
        'modSecStr',
        'featuresStr',
        'oauthStr',
        'remoteStr',
        'serverSideStr',
      ];
      for (let key of keysToUpdate) {
        if (langData.hasOwnProperty(key)) {
          this[key] = langData[key];
        }
      }
    });
  }
}


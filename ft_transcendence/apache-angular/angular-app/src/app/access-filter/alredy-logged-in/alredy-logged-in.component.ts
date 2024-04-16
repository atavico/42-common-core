import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { LanguageService } from '../../service/language.service';

@Component({
  selector: 'app-alredy-logged-in',
  templateUrl: './alredy-logged-in.component.html',
  styleUrls: ['./alredy-logged-in.component.css'],
})
export class AlredyLoggedInComponent {
  // Html variables
  back: string = 'Back';
  alredyLoggedIn: string =
    'You are already logged in. Please log out to log in again.';

  constructor(
    private router: Router,
    private languageService: LanguageService
  ) {}

  ngOnInit(): void {
    this.updateLocalizedStrings();
  }

  [key: string]: any;

  updateLocalizedStrings() {
    this.languageService.getLanguageData().subscribe((data) => {
      const langData = data[localStorage.getItem('language') || 'en'];
      const keysToUpdate = ['back', 'alredyLoggedIn'];
      for (const key of keysToUpdate) {
        if (langData.hasOwnProperty(key)) {
          this[key] = langData[key];
        }
      }
    });
  }

  goBack() {
    localStorage.removeItem('token');
    this.router.navigate(['']);
  }
}

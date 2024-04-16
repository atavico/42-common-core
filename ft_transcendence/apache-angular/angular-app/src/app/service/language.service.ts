import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root',
})
export class LanguageService {
  private _jsonURL = 'assets/language.json';
  private languageData: any;

  constructor(private http: HttpClient) {
    this.loadJSON();
  }

  private loadJSON(): void {
    this.http.get(this._jsonURL).subscribe(data => {
      this.languageData = data;
    });
  }

  public getLanguageData(): Observable<any> {
    return this.http.get(this._jsonURL);
  }
}

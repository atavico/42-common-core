// angular imports
import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { ReactiveFormsModule } from '@angular/forms';
import { FormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
// access-filter
import { AccessFilterComponent } from './access-filter/access-filter.component';
import { SignUpComponent } from './access-filter/sign-up/sign-up.component';
import { LogInComponent } from './access-filter/log-in/log-in.component';
// service
import { LanguageService } from './service/language.service';
import { AuthService } from './service/auth.service';
// main-menu
import { SidePanelComponent } from './main-menu/side-panel/side-panel.component';
import { MainMenuComponent } from './main-menu/main-menu.component';
import { SettingsComponent } from './main-menu/settings/settings.component';
import { AddFriendComponent } from './main-menu/add-friend/add-friend.component';
import { ProfileComponent } from './main-menu/profile/profile.component';
import { PlayButtonComponent } from './main-menu/play-button/play-button.component';
// gameRemote
import { EndGameComponent } from './game/end-game/end-game.component';
import { HostMenuComponent } from './game/host-menu/host-menu.component';
import { LobbyComponent } from './game/lobby/lobby.component';
import { MatchHeaderComponent } from './game/lobby/match-header/match-header.component';
import { MatchesComponent } from './game/lobby/matches/matches.component';
import { MatchComponent } from './game/match/match.component';
import { PanelSideComponent } from './game/panel-side/panel-side.component';
import { QueueComponent } from './game/queue/queue.component';
import { TournamentPreComponent } from './game/tournament-pre/tournament-pre.component';
// gameLocal
import { LocalGame } from './gameLocal/local-game.service';
import { MatchLocalService } from './gameLocal/local-game.service';
import { LobbyLocalComponent } from './gameLocal/lobby-local/lobby-local.component';
// other imports
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { Global } from './shared/global';
import { HeaderComponent } from './header/header/header.component';
import { FooterComponent } from './header/footer/footer.component';
import { AlredyLoggedInComponent } from './access-filter/alredy-logged-in/alredy-logged-in.component';
import { MatchLocalComponent } from './gameLocal/match-local/match-local.component';
import { EndOneComponent } from './gameLocal/end-one/end-one.component';
import { TournamentLocalComponent } from './gameLocal/tournament-local/tournament-local.component';

@NgModule({
  declarations: [
    AppComponent,
    AccessFilterComponent,
    SignUpComponent,
    LogInComponent,
    SidePanelComponent,
    MainMenuComponent,
    SettingsComponent,
    AddFriendComponent,
    ProfileComponent,
    QueueComponent,
    LobbyComponent,
    HostMenuComponent,
    EndGameComponent,
    PlayButtonComponent,
    MatchComponent,
    HeaderComponent,
    FooterComponent,
    PanelSideComponent,
    AlredyLoggedInComponent,
    TournamentPreComponent,
    MatchesComponent,
    MatchHeaderComponent,
    LobbyLocalComponent,
    MatchLocalComponent,
    EndOneComponent,
    TournamentLocalComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    ReactiveFormsModule,
    HttpClientModule,
    BrowserAnimationsModule,
    FormsModule,
  ],
  providers: [LanguageService, Global, AuthService, LocalGame, MatchLocalService],
  bootstrap: [AppComponent],
})
export class AppModule {}

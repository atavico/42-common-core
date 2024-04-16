// angular imports
import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
// access-filter
import { AccessFilterComponent } from './access-filter/access-filter.component';
import { SignUpComponent } from './access-filter/sign-up/sign-up.component';
import { LogInComponent } from './access-filter/log-in/log-in.component';
import { AlredyLoggedInComponent } from './access-filter/alredy-logged-in/alredy-logged-in.component';
// main-menu
import { SidePanelComponent } from './main-menu/side-panel/side-panel.component';
import { MainMenuComponent } from './main-menu/main-menu.component';
// gameTournament
import { QueueComponent } from './game/queue/queue.component';
import { LobbyComponent } from './game/lobby/lobby.component';
import { HostMenuComponent } from './game/host-menu/host-menu.component';
import { MatchComponent } from './game/match/match.component';
import { EndGameComponent } from './game/end-game/end-game.component';
// gameLocal
import { LobbyLocalComponent } from './gameLocal/lobby-local/lobby-local.component';
import { MatchLocalComponent } from './gameLocal/match-local/match-local.component';
import { EndOneComponent } from './gameLocal/end-one/end-one.component';
import { TournamentLocalComponent } from './gameLocal/tournament-local/tournament-local.component';
// other imports
import { TournamentPreComponent } from './game/tournament-pre/tournament-pre.component';

const routes: Routes = [
  { path: '', component: AccessFilterComponent },
  { path: 'sign-up', component: SignUpComponent },
  { path: 'log-in', component: LogInComponent },
  { path: 'alredy-logged-in', component: AlredyLoggedInComponent },
  { path: 'main-menu', component: MainMenuComponent },
  { path: 'side-panel', component: SidePanelComponent },
  { path: 'queue', component: QueueComponent },
  { path: 'lobby', component: LobbyComponent },
  { path: 'host-menu', component: HostMenuComponent },
  { path: 'tournament-pre', component: TournamentPreComponent },
  { path: 'match', component: MatchComponent },
  { path: 'end-game', component: EndGameComponent },
  { path: 'lobby-local', component: LobbyLocalComponent },
  { path: 'match-local', component: MatchLocalComponent },
  { path: 'end-one', component: EndOneComponent },
  { path: 'tournament-local', component: TournamentLocalComponent },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule],
})
export class AppRoutingModule {}

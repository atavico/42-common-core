export interface Tournament {
    tournament_name: string;
    game_type: string;
    friends_only: boolean;
    password: boolean;
    score_to_win: number;
    max_partecipants: number;
    creator: number;
    status: string;
    players_id: string;
    placements: string;
    is_active: boolean;
}

export class Tournament implements Tournament{
    // tournament_name: string;
    // game_type: string;
    // friends_only: boolean;
    // password: string;
    // score_to_win: number;
    // max_partecipants: number;
    // creator: number;
    // status: string;
    // players_id: string;
    // placements: string;
    // is_active: boolean;

    constructor() {
        this.tournament_name = 'Tournament X';
        this.game_type = 'tournament';
        this.friends_only = false;
        this.password = false;
        this.score_to_win = 3;
        this.max_partecipants = 8;
        this.creator = 1;
        this.status = 'pending';
        this.players_id = '[]';
        this.placements = '[]';
        this.is_active = true;
    }
}

//     getTournament_name() { return (this.tournament_name) }
//     getGame_type() { return(this.game_type) }
//     getFriends_only() { return(this.friends_only) }
//     getPassword() { return(this.password) }
//     getScore_to_win() { return(this.score_to_win) }
//     getMax_partecipants() { return(this.max_partecipants) }
//     getCreator() { return(this.creator) }
//     getStatus() { return(this.status) }
//     getPlayer_id() { return(this.player_id) }
//     getPlacements() { return(this.placements) }
//     getIs_active() { return(this.is_active) }

//     setTournament_name(tournament_name: string) { this.tournament_name = tournament_name }
//     setGame_type(game_type: string) { this.game_type = game_type }
//     setFriends_only(friends_only: boolean) { this.friends_only = friends_only }
//     setPassword(password: string) { this.password = password }
//     setScore_to_win(score_to_win: number) { this.score_to_win = score_to_win }
//     setMax_partecipants(max_partecipants: number) { this.max_partecipants = max_partecipants }
//     setCreator(creator: number) { this.creator = creator }
//     setStatus(status: string) { this.status = status }
//     setPlayer_id(player_id: string) { this.player_id = player_id }
//     setPlacements(placements: string) { this.placements = placements }
//     setIs_active(is_active: boolean) { this.is_active = is_active }
// }

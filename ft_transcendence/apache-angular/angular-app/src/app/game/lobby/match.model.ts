export class Match {
  constructor(
    public creator: number,
    public friends_only: boolean,
    public game_type: string,
    public id: number,
    public is_active: boolean,
    public max_partecipants: number,
    public password: boolean,
    public placements: string,
    public players_id: string,
    public score_to_win: number,
    public started: string,
    public status: string,  // 'pending' | 'started' | 'finished'
    public tournament_name: string
  ) {}
}

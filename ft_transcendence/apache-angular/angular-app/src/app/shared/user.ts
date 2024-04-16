export class User {
  private _id: number;
  private _nickname: string;
  private _email: string;
  private _avatar: string;
  private _games_played: number;
  private _games_won: number;
  private _games_lost: number;
  private _language: string;
  private _token: string;
  private _friend_list: Array<number>;
  private _tournaments_played: number;
  private _tournaments_placements: Array<number>;

  constructor() {
    //Todo: reset to empty
    this._id = 123;
    this._nickname = 'UserQWE';
    this._email = 'asd@asd.com';
    this._avatar = "";
    this._games_played = 0;
    this._games_won = 0;
    this._games_lost = 0;
    this._language = 'en';
    this._token = '';
    this._friend_list = [1, 2, 3];
    this._tournaments_played = 0;
    this._tournaments_placements = [];
  }

  setUser(data: any) {
    this._id = data.player_id;
    this._nickname = data.username;
    this._email = data.email;
    if (data.avatar.startsWith('data:image/')) {
      this._avatar = data.avatar;
    } else {
      this.choseProfilePic(data);
    }
    this._games_played = 0;
    this._games_won = data.games_won;
    this._games_lost = data.games_lost;
    this._language = data.language;
    this._token = data.Token;
    this._friend_list = JSON.parse(data.friend_list);
    this._tournaments_played = JSON.parse(data.tournaments_played);
    this._tournaments_placements = JSON.parse(data.tournaments_placements);
  }

  setUserBySignup(data: any) {
    data = JSON.parse(data);
    // //console.log('setUserBySignup: ', data.data);
    this._id = data.data.player_id;
    this._nickname = data.data.username;
    this._email = data.data.email;
    if (data.data.avatar.startsWith('data:image/')) {
      this._avatar = data.data.avatar;
    } else {
      this.choseProfilePic(data);
    }
    this._games_played = data.data.games_played;
    this._games_won = data.data.games_won;
    this._games_lost = data.data.games_lost;
    this._language = data.data.language;
    this._token = data.data.Token;
    this._friend_list = JSON.parse(data.data.friend_list);
    this._tournaments_played = JSON.parse(data.data.tournaments_played);
    this._tournaments_placements = JSON.parse(data.data.tournaments_placements);
  }

  setUserByLogin(data: any) {
    data = JSON.parse(data);
    //console.log('setUserByLogin: ', data.data);
    this._id = data.data.player_id;
    this._nickname = data.data.username;
    this._email = data.data.email;
    if (data.data.avatar.startsWith('data:image/')) {
      this._avatar = data.data.avatar;
    } else {
      this._avatar = 'assets/profilePic/defProfilePic.png';
    }
    this._games_played = data.data.games_played;
    this._games_won = data.data.games_won;
    this._games_lost = data.data.games_lost;
    this._language = data.data.language;
    this._token = data.token;
    this._friend_list = JSON.parse(data.data.friend_list);
    this._tournaments_played = JSON.parse(data.data.tournaments_played);
    this._tournaments_placements = JSON.parse(data.data.tournaments_placements);
  }

  //----------------------------------------------------------

  setId(id: number) {
    this._id = id;
  }
  setNickname(nickname: string) {
    this._nickname = nickname;
  }
  setEmail(email: string) {
    this._email = email;
  }
  setAvatar(avatar: string = 'assets/profilePic/defProfilePic.png') {
    this._avatar = avatar;
  }
  setGamesPlayed(games_played: number) {
    this._games_played = games_played;
  }
  setGamesWon(games_won: number) {
    this._games_won = games_won;
  }
  setGamesLost(games_lost: number) {
    this._games_lost = games_lost;
  }
  setLanguage(language: string) {
    this._language = language;
  }
  setToken(token: string) {
    this._token = token;
  }
  setTournamentsPlayed(tournaments_played: number) {
    this._tournaments_played = tournaments_played;
  }
  setTournamentsPlacements(tournaments_placements: Array<number>) {
    this._tournaments_placements = tournaments_placements;
  }

  //--------------------Friend Stuff--------------------

  setFriendList(friend_list: Array<number>) {
    this._friend_list = friend_list;
  }
  removeFriend(id: number) {
    this._friend_list = this._friend_list.filter((value) => value !== id);
  }
  addFriend(id: number) {
    this._friend_list.push(id);
  }
  getFriendList() {
    return this._friend_list;
  }
  cleanFriendList() {
    this._friend_list = [];
  }

  //--------------------------------------------------

  getId() {
    return this._id;
  }
  getNickname() {
    return this._nickname;
  }
  getEmail() {
    return this._email;
  }
  getAvatar() {
    return this._avatar;
  }
  getGamesPlayed() {
    return this._games_played;
  }
  getGamesWon() {
    return this._games_won;
  }
  getGamesLost() {
    return this._games_lost;
  }
  getLanguage() {
    return this._language;
  }
  getToken() {
    return this._token;
  }
  getTournamentsPlayed() {
    return this._tournaments_played;
  }
  getTournamentsPlacements() {
    return this._tournaments_placements;
  }

  clear() {
    this._id = 0;
    this._nickname = '';
    this._email = '';
    this._avatar = '';
    this._games_played = 0;
    this._games_won = 0;
    this._games_lost = 0;
    this._language = '';
    this._token = '';
    this._friend_list = [];
  }

  choseProfilePic(data: any) {
    const nick = data.data.username.toLowerCase();
    const avatarMap: { [key: string]: string } = {
      cat: 'assets/profilePic/cat.png',
      dog: 'assets/profilePic/dog.png',
      cow: 'assets/profilePic/cow.png',
      pig: 'assets/profilePic/pig.png',
      ant: 'assets/profilePic/ant.png',
      bat: 'assets/profilePic/bat.png',
      bee: 'assets/profilePic/bee.png',
      fox: 'assets/profilePic/fox.png',
      rat: 'assets/profilePic/rat.png',
      hen: 'assets/profilePic/hen.png',
      owl: 'assets/profilePic/owl.png',
      elk: 'assets/profilePic/elk.png',
      ape: 'assets/profilePic/ape.png',
      boa: 'assets/profilePic/boa.png',
      koi: 'assets/profilePic/koi.png',
    };
    // send in base64
    const imgSrc = avatarMap[nick] || 'assets/profilePic/defProfilePic.png';
    
    let img = new Image();
    img.src = imgSrc;
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
        this._avatar = dataUrl;
      }
    }
  }
}

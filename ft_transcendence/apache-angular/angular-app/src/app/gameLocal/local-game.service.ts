export class LocalGame {
  partecipants: { nick: string; avatar: string; id: number }[] = [];

  nextMatch: {
    nick1: string;
    avatar1: string;
    nick2: string;
    avatar2: string;
  } = { nick1: '', avatar1: '', nick2: '', avatar2: '' };

  finals: string[][] = [['', '']];
  semifinals: string[][] = [
    ['', ''],
    ['', ''],
  ];

  score: Number[] = [0, 0];

  turn: string = '';

  tournementOrSolo: boolean = false;

  idMatch: number = 0;

  cleanClass() {
    this.partecipants = [];
    this.nextMatch = { nick1: '', avatar1: '', nick2: '', avatar2: '' };
    this.finals = [['', '']];
    this.semifinals = [
      ['', ''],
      ['', ''],
    ];
    this.score = [0, 0];
    this.turn = '';
    this.tournementOrSolo = false;
    this.idMatch = 0;
  }
}

export class MatchLocalService {
  BALL_MAX_SPEED: number = 90;
  PADDLE_SPEED: number = 52;
  PADDLE_H: number = 24;
  PADDLE_W: number = 2;
  PADDLE_O: number = 3;

  score_to_win: number = 3;
  game_speed: number = 11;
  paddle_speed: number = this.PADDLE_SPEED;
  score: number[] = [0, 0];
  ball_speed: number = 10;
  paddles_y: number[] = [50, 50];
  ball_pos: number[] = [50, 50];
  ball_dir: number = this.init_angle();
  timestamp: number = 0;
  key_up_pressed: boolean[] = [false, false];
  key_down_pressed: boolean[] = [false, false];

  init_angle() {
    this.ball_dir = Math.random() * 50 + (Math.random() > 0.5 ? 180 : 0);
    this.reset_ball_direction();
    return this.ball_dir;
  }

  reinit() {
    this.ball_pos = [50, 50];
    this.init_angle();
    this.ball_speed = 11;
    this.timestamp = 0;
  }

  raise_ball_speed(dt: number) {
    if (this.ball_speed <= this.BALL_MAX_SPEED) {
      this.ball_speed += this.game_speed * dt;
    }
  }

  degToRadiants(degree: number) {
    return degree * (Math.PI / 180);
  }

  move_ball_and_collide() {
    let dt = (Date.now() - this.timestamp) / 1000;
    // console.log('dt: ', dt);
    if (this.timestamp == 0) dt = 0;
    this.timestamp = Date.now();

    this.move_paddles(dt);
    this.raise_ball_speed(dt);

    this.horizontal_axe_collisions();
    this.vertical_axe_collisions();
    this.paddles_collisions();

    let dx = this.ball_speed * Math.cos(this.degToRadiants(this.ball_dir)) * dt;
    let dy = this.ball_speed * Math.sin(this.degToRadiants(this.ball_dir)) * dt;
    this.ball_pos[0] += dx;
    this.ball_pos[1] += dy;

    // return this.ball_pos;
  }

  move_paddles(dt: number) {
    for (let i = 0; i < 2; i++) {
      if (this.key_up_pressed[i]) {
        this.paddles_y[i] -= this.paddle_speed * dt;
      } else if (this.key_down_pressed[i]) {
        this.paddles_y[i] += this.paddle_speed * dt;
      }
      if (this.paddles_y[i] < this.PADDLE_H / 2) {
        this.paddles_y[i] = this.PADDLE_H / 2;
      } else if (this.paddles_y[i] > 100 - this.PADDLE_H / 2) {
        this.paddles_y[i] = 100 - this.PADDLE_H / 2;
      }
    }
  }

  key_pressed(key: string, pressed: boolean) {
    if (key == 'ArrowDown') {
      this.key_down_pressed[1] = pressed;
      if (pressed === true)
        this.key_up_pressed[1] = !pressed;
    } else if (key == 'ArrowUp') {
      this.key_up_pressed[1] = pressed;
      if (pressed === true)
        this.key_down_pressed[1] = !pressed;
    } else if (key == 's') {
      this.key_down_pressed[0] = pressed;
      if (pressed === true)
        this.key_up_pressed[0] = !pressed;
    } else if (key == 'w') {
      this.key_up_pressed[0] = pressed;
      if (pressed === true)
        this.key_down_pressed[0] = !pressed;
    }
  }

  reset_ball_direction() {
    this.ball_dir = this.ball_dir % 360;
    if (this.ball_dir < 0) {
      this.ball_dir += 360;
    }
  }

  horizontal_axe_collisions() {
    let y = this.ball_pos[1];
    if (y > 98 && 0 < this.ball_dir && this.ball_dir < 180) {
      this.ball_dir = 180 - this.ball_dir + 180;
    }
    if (y < 2 && 180 < this.ball_dir && this.ball_dir < 360) {
      this.ball_dir = 180 - this.ball_dir - 180;
    }
    this.reset_ball_direction();
  }

  vertical_axe_collisions() {
    let x = this.ball_pos[0];
    if (x < 1) {
      this.raise_score(1);
    } else if (x > 99) {
      this.raise_score(0);
    }
    if (x < 1 || x > 99) {
      this.reinit();
    }
  }

  raise_score(idx: number) {
    this.score[idx] += 1;
  }

  paddles_collisions() {
    let bx = this.ball_pos[0];
    let by = this.ball_pos[1];
    if (this.PADDLE_O - 1 <= bx && bx <= this.PADDLE_O + this.PADDLE_W + 1) {
      if (
        this.paddles_y[0] - this.PADDLE_H / 2 < by &&
        by < this.paddles_y[0] + this.PADDLE_H / 2
      ) {
        if (90 <= this.ball_dir && this.ball_dir < 270) {
          this.ball_dir = 90 - this.ball_dir + 90;
          let dx = this.paddles_y[0] - by;
          this.ball_dir -= dx * 2.5;
          this.reset_ball_direction();
        }
      }
    } else if (
      100 - this.PADDLE_O - this.PADDLE_W - 1 <= bx &&
      bx <= 100 - this.PADDLE_O + 1
    ) {
      if (
        this.paddles_y[1] - this.PADDLE_H / 2 < by &&
        by < this.paddles_y[1] + this.PADDLE_H / 2
      ) {
        // console.log('dir: ', this.ball_dir, '  pos_paddle: ', this.paddles_y[1]);
        if (
          (0 <= this.ball_dir && this.ball_dir <= 90) ||
          (270 < this.ball_dir && this.ball_dir <= 360)
        ) {
          this.ball_dir = 90 - this.ball_dir + 90;
          let dx = this.paddles_y[1] - by;
          this.ball_dir += dx * 2.5;
          this.reset_ball_direction();
        }
      }
    }
  }

  game_end() {
    for (let i = 0; i < 2; i++) {
      if (this.score[i] >= this.score_to_win) {
        return i;
      }
    }
    return -1;
  }

  set_winner(idx: number) {
    this.score[idx] = this.score_to_win;
  }

  dict() {
    return {
      score: this.score,
      paddles_y: this.paddles_y,
      ball_pos: this.ball_pos,
      ball_speed: this.ball_speed,
      ball_dir: this.ball_dir,
    };
  }
}

// BALL_MAX_SPEED = 90
// PADDLE_SPEED = 52
// PADDLE_H = 24
// PADDLE_W = 2
// PADDLE_O = 3

// def __init__(self, score_to_win:int=0, *args, **kwargs) -> None:
//     self.score_to_win:int = score_to_win
//     self.game_speed:float = 11
//     self.max_ball_speed:float = BALL_MAX_SPEED
//     self.paddle_speed:float = PADDLE_SPEED
//     self.score:list = [0, 0]
//     self.ball_speed:float = 10.0
//     self.paddles_y:list = [50, 50]
//     self.ball_pos:list = [50, 50]
//     self.ball_dir:float = self.init_angle()
//     self.timestamp:float = 0
//     self.key_up_pressed:list = [False, False]
//     self.key_down_pressed:list = [False, False]

// def init_angle(self) -> float:
//     self.ball_dir = uniform(-50, 50) + choice([180, 0])
//     # self.ball_dir = uniform(305, 360)
//     self.reset_ball_direction()
//     return self.ball_dir

// def reinit(self) -> None:
//     self.ball_pos   = [50, 50]
//     self.init_angle()
//     self.ball_speed = 11
//     self.timestamp  = 0
//     # TODO: Set pause, wait a second for the new game

// def raise_ball_speed(self, dt:float) -> None:
//     if self.ball_speed <= self.max_ball_speed:
//         self.ball_speed += self.game_speed * dt

// def move_ball_and_collide(self) -> list:
//     dt:float = time.time() - self.timestamp
//     if self.timestamp == 0: dt = 0
//     self.timestamp = time.time()

//     self.move_paddles(dt)
//     self.raise_ball_speed(dt)

//     self.horizontal_axe_collisions()
//     self.vertical_axe_collisions()
//     self.paddles_collisions()

//     dx = (self.ball_speed * cos(radians(self.ball_dir))) * dt
//     dy = (self.ball_speed * sin(radians(self.ball_dir))) * dt
//     self.ball_pos[0] += dx
//     self.ball_pos[1] += dy

//     # printd(f"{self.dict()}")
//     return self.ball_pos

// def move_paddles(self, dt:float) -> None:
//     for i in range(2):
//         if self.key_up_pressed[i]:
//             self.paddles_y[i] -= self.paddle_speed * dt
//         elif self.key_down_pressed[i]:
//             self.paddles_y[i] += self.paddle_speed * dt
//         if self.paddles_y[i] < PADDLE_H / 2:
//             self.paddles_y[i] = PADDLE_H / 2
//         elif self.paddles_y[i] > 100 - (PADDLE_H / 2):
//             self.paddles_y[i] = 100 - (PADDLE_H / 2)

// async def key_pressed(self, pid:int, key:str, pressed:bool) -> None:
//     # printd(f"Player <{pid}> pressed {key} -> {pressed}")
//     if key == "ArrowDown":
//         self.key_down_pressed[pid] = pressed
//     elif key == "ArrowUp":
//         self.key_up_pressed[pid] = pressed

// def reset_ball_direction(self) -> None:
//     self.ball_dir %= 360

// def horizontal_axe_collisions(self) -> None:
//     y = self.ball_pos[1]
//     if y > 98 and ( 0 < self.ball_dir < 180):
//         self.ball_dir = (180 - self.ball_dir) + 180
//     if y < 2 and ( 180 < self.ball_dir < 360):
//         self.ball_dir = (180 - self.ball_dir) - 180
//     self.reset_ball_direction()

// def vertical_axe_collisions(self) -> None:
//     x = self.ball_pos[0]
//     if x < 1:
//         self.raise_score(1)
//     elif x > 99:
//         self.raise_score(0)
//     if x < 1 or x > 99:
//         self.reinit()

// def raise_score(self, idx:int) -> None:
//     self.score[idx] += 1

// def paddles_collisions(self) -> None:
//     bx = self.ball_pos[0]
//     by = self.ball_pos[1]
//     if PADDLE_O - 1 <= bx <= PADDLE_O + PADDLE_W + 1:
//         if self.paddles_y[0] - PADDLE_H / 2 < by < self.paddles_y[0] + PADDLE_H / 2:
//             if 90 <= self.ball_dir < 270:
//                 self.ball_dir = (90 - self.ball_dir) + 90
//                 dx = self.paddles_y[0] - by
//                 self.ball_dir -= dx * 2.5
//     elif (100 - PADDLE_O - PADDLE_W - 1) <= bx <= (100 - PADDLE_O + 1):
//         if self.paddles_y[1] - PADDLE_H / 2 < by < self.paddles_y[1] + PADDLE_H / 2:
//             if 0 <= self.ball_dir <= 90 or 270 < self.ball_dir <= 360:
//                 self.ball_dir = (90 - self.ball_dir) + 90
//                 dx = self.paddles_y[1] - by
//                 self.ball_dir += dx * 2.5
//     self.reset_ball_direction()

// async def game_end(self) -> int:
//     for i in range(2):
//         if self.score[i] >= self.score_to_win:
//             return i
//     return -1

// def start(self) -> None:
//     #TODO: Timer to begin (send that to all users too)
//     pass

// def set_winner(self, idx:int) -> None:
//     self.score[idx] = self.score_to_win

// def dict(self) -> dict:
//     return {
//         "score": self.score,
//         "paddles_y": self.paddles_y,
//         "ball_pos": self.ball_pos,
//         "ball_speed": self.ball_speed,
//         "ball_dir": self.ball_dir
//     }

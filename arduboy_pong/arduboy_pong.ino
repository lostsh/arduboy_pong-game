#include <Arduboy2.h>
Arduboy2 ard;

float x, y, dx, dy, bSpeed;
float yRacketLeft, yRacketRight, rSpeed, rSize;
unsigned int scoreP1, scoreP2;

#define MAX_BALL_SPEED 2.0
#define MIN_BALL_SPEED 0.5
#define MAX_RACKET_SIZE 15
#define MIN_RACKET_SIZE 5
#define MAX_RACKET_SPEED 1.2
#define MIN_RACKET_SPEED 0.09

/**
 * 0 == Menu
 * 1 == Game
 * 2 == settings
 */
unsigned int gameMode;
int settingCursor;

void setup() {
  ard.begin();
  ard.setFrameRate(15);

  yRacketLeft = 0;
  yRacketRight = -1;
  bSpeed = 1.6;
  rSpeed = 0.2;
  rSize = 10;
  gameMode = 0;
  settingCursor = 3;

  dx=-0.09;
  dy=0.1;
  bSpeed = 0.15;
  initGameVars();
}

void loop() {
  switch(gameMode){
    case 0:
    menu();
    break;
    case 1:
    game();
    break;
    case 2:
    setting(&settingCursor, &bSpeed, &rSize, &rSpeed);
    break;
    default:
    menu();
    break;
  }
}

void initGameVars(){
  x = WIDTH/2;
  y = HEIGHT/2;
  scoreP1 = 0;
  scoreP2 = 0;
  setBallSpeed(bSpeed);
}

void setBallSpeed(const float speedVal){
  dx=-speedVal+0.02;
  dy=+speedVal-0.02;
}

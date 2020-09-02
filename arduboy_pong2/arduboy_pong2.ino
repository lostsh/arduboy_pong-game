#include <Arduboy2.h>
Arduboy2 ard;

#define DXYMIN 0.1
float x, y, dx, dy;
float yRacketLeft, yRacketRight, rSpeed=0.2;
int rSize=10;
unsigned int scoreP1, scoreP2;
bool inMenu, inSetting;

void setup() {
  ard.begin();
  ard.setFrameRate(15);
  initVars();
}

void loop() {
  if(inMenu){
    menu();
  }else{
    game();
  }
  if(isBallOutOfLimit(x, y)){
    inMenu = true;
    initGameVars();
  }
  if(ard.pressed(A_BUTTON)){
    delay(200);
    inMenu=!inMenu;
  }
}

void initVars(){
  yRacketLeft = 0;
  yRacketRight = -1;
  initGameVars();
  
  inMenu = true;
  inSetting = false;
}
void initGameVars(){
  x = WIDTH/2;
  y = HEIGHT/2;
  dx=-0.09;
  dy=0.1;
  scoreP1 = 0;
  scoreP2 = 0;
}

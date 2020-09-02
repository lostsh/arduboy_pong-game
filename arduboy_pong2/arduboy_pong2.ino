#include <Arduboy2.h>
Arduboy2 ard;

float x=WIDTH/2, y=HEIGHT/2, dx, dy;
float yRacketLeft, yRacketRight, rSize=10, rSpeed=0.2;
unsigned int scoreP1=0, scoreP2=0;

void setup() {
  ard.begin();
  ard.setFrameRate(15);
  
  dx=-0.09;
  dy=0.1;
}

void loop() {
  game();
}

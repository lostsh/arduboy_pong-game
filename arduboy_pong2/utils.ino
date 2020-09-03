void drawWalls(bool top, bool right, bool bottom, bool left){
  if(top){
    ard.drawLine(0,0,WIDTH,0);
  }
  if(right){
    ard.drawLine(WIDTH-1,0,WIDTH-1,HEIGHT-1);
  }
  if(bottom){
    ard.drawLine(0,HEIGHT-1,WIDTH-1,HEIGHT-1);
  }
  if(left){
    ard.drawLine(0,0,0,HEIGHT-1);
  }
}

void drawBall(const int x, const int y){
  ard.drawLine(x-1,y-1,x-1,y+1);//left
  ard.drawLine(x,y-1,x,y+1);//midle
  ard.drawLine(x+1,y-1,x+1,y+1);//right
}

void updateBallSpeed(bool increase){
  if(increase){
    dx=dx*1.6;
    dy=dy*1.6;
  }else{
    //decrease speed please
    if(dx > DXYMIN){
      dx=dx*0.95;
    }
    if(dy > DXYMIN){
      dy=dy*0.95;
    }
  }
}
void mooveBall(float *x, float *y, const float dx, const float dy){
  if(!isBallOutOfLimit(*x, *y)){
    *x+=dx;
    *y+=dy;
  }
}

bool isBallOutOfLimit(const float x, const float y){
  return (x<0 || x >WIDTH || y<0 || y>HEIGHT);
}

void drawRacket(const float yRacketLeft, const float yRacketRight, const int rSize){
  if(yRacketLeft >= 0){
    ard.drawLine(0,yRacketLeft,0,yRacketLeft+rSize);
    ard.drawLine(1,yRacketLeft,1,yRacketLeft+rSize);
  }
  if(yRacketRight >= 0){
    ard.drawLine(WIDTH-1,yRacketRight,WIDTH-1,yRacketRight+rSize);
    ard.drawLine(WIDTH-2,yRacketRight,WIDTH-2,yRacketRight+rSize);
  }
}

void drawGameOver(){
  ard.clear();
  ard.setCursor(13, 22);
  ard.setTextSize(2);
  ard.print("GAME OVER");
  ard.setTextSize(1);
  ard.display();
}

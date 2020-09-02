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

void drawRacket(const int yRacketLeft, const int yRacketRight, const int bSize){
  if(yRacketLeft >= 0){
    ard.drawLine(0,yRacketLeft,0,yRacketLeft+bSize);
    ard.drawLine(1,yRacketLeft,1,yRacketLeft+bSize);
  }
  if(yRacketRight >= 0){
    ard.drawLine(WIDTH-1,yRacketRight,WIDTH-1,yRacketRight+bSize);
    ard.drawLine(WIDTH-2,yRacketRight,WIDTH-2,yRacketRight+bSize);
  }
}

void drawGameOver(){
  ard.clear();
  ard.setCursor(16, 21);
  ard.setTextSize(2);
  ard.print("GAME OVER");
  ard.setTextSize(1);
  ard.display();
}

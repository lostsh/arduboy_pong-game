void game(){
  ard.clear();
  drawWalls(true, yRacketRight<0, true, yRacketLeft<0);
  if(yRacketRight>=0){
    drawMidLine();
  }
  mooveBall(&x, &y, dx, dy);
  drawBall(x,y);
  mooveRacket();
  drawRacket(yRacketLeft, yRacketRight, rSize);
  bounce(&x, &y, &dx, &dy, yRacketLeft, yRacketRight, rSize);
  if(isBallOutOfLimit(x, y)){
    drawGameOver();
    delay(1200);
    initGameVars();
    //=================================================================just for test
    gameMode = 0;
  }
  ard.display();
}





void bounce(float *x, float *y, float *dx, float *dy, const float yRacketLeft, const float yRacketRight, const float rSize){
  if(*y+1>HEIGHT-1 or *y-1<1){//top or bottom
    *dy=-*dy;
  }
  //if there is no player right or the ball is on the racket then bounce
  if( yRacketRight<0 && *x+1>WIDTH-1 || (yRacketRight>=0 && *x+1>WIDTH-1 && yRacketRight<=*y&&*y<=yRacketRight+rSize) ){
    *dx=-*dx;
    //speed increase
    if(*x+1>WIDTH-1 && ((yRacketRight <= *y && *y <= yRacketRight+1) or (yRacketRight+rSize-1 <= *y && *y <= yRacketRight+rSize))){
      updateBallAngle(true);
    }else{
      //decrease ball speed
    }
  }
  //if there is no player left of the ball is on the racket then bounce
  if((yRacketLeft<0 && *x-1<1) or (yRacketLeft>=0 && *x-1<1 && (yRacketLeft <= *y && yRacketLeft+rSize >= *y))){
    *dx=-*dx;
    //speed increase
    if(*x-1<1 && ((yRacketLeft <= *y && *y <= yRacketLeft+1) or (yRacketLeft+rSize-1 <= *y && *y <= yRacketLeft+rSize))){
      updateBallAngle(true);
    }else{
      //decrease ball speed
    }
  }
}
void mooveRacket(){
  if(yRacketLeft >= 0){
    if(ard.pressed(UP_BUTTON) and yRacketLeft-rSpeed>0){
      yRacketLeft-=rSpeed;
    }
    if(ard.pressed(DOWN_BUTTON) and yRacketLeft+rSize+rSpeed<HEIGHT){
      yRacketLeft+=rSpeed;
    }
  }

  if(yRacketRight >= 0){
    if(ard.pressed(B_BUTTON) and yRacketRight-rSpeed>0){
      yRacketRight-=rSpeed;
    }
    if(ard.pressed(A_BUTTON) and yRacketRight+rSize+rSpeed<HEIGHT){
      yRacketRight+=rSpeed;
    }
  }
}



//=============================================================================================================================================



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
void drawMidLine(){
  for(int i=0;i<=HEIGHT;i+=8){
    ard.drawLine((WIDTH/2)-1,i,(WIDTH/2)-1,i+4);
    ard.drawLine(WIDTH/2,i,WIDTH/2,i+4);
    ard.drawLine((WIDTH/2)+1,i,(WIDTH/2)+1,i+4);
  }
}

void drawBall(const int x, const int y){
  ard.drawLine(x-1,y-1,x-1,y+1);//left
  ard.drawLine(x,y-1,x,y+1);//midle
  ard.drawLine(x+1,y-1,x+1,y+1);//right
}

void updateBallAngle(bool increase){
  //================================just to do not foret this is the way to bounce on the top & the bottom of the racket
  //only a test okay ?
  /*
  if(y <= yRacletLeft || y <= yRacletRigth){
    dy=-dy;
  }
  if(y >= yRacletLeft+rSize || y >= yRacletRigth+rSize){
    dx=-dx;
  }*/
  //================================
  if(increase){
    //increase speed, update angle
  }else{
    //decrease speed please
    if(dx > MIN_BALL_SPEED){
      dx=dx*0.95;
    }
    if(dy > MIN_BALL_SPEED){
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
  return (x < -1 || x > WIDTH+1 || y < -1 || y > HEIGHT+1);
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

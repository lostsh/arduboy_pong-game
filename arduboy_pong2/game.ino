void game(){
  ard.clear();
  mooveBall(&x, &y, dx, dy);
  drawBall(x,y);
  drawWalls(true, true, true, false);
  mooveRacket();
  drawRacket(yRacketLeft, -1, rSize);
  bounce(&x, &y, &dx, &dy, yRacketLeft, yRacketRight, rSize);
  if(isBallOutOfLimit(x, y)){
    drawGameOver();
    delay(1200);
  }
  ard.display();
}
void menu(){
  ard.clear();
  ard.setCursor(30, 5);
  ard.setTextSize(3);
  ard.print("PONG");
  ard.setTextSize(1);
  ard.display();
}
void settings(int *celerity, int *racketSize){  
}
void bounce(float *x, float *y, float *dx, float *dy, const float yRacketLeft, const float yRacketRight, const int rSize){
  if(*y+1>HEIGHT-1 or *y-1<1){//top or bottom
    *dy=-*dy;
  }
  //if there is no player right or the ball is on the racket then bounce
  if( yRacketRight<0 && *x+1>WIDTH-1 || (yRacketRight>=0 && *x+1>WIDTH-1 && yRacketRight<=*y&&*y<=yRacketRight+rSize) ){
    *dx=-*dx;
    //speed increase
    if(*x+1>WIDTH-1 && ((yRacketRight <= *y && *y <= yRacketRight+1) or (yRacketRight+rSize-1 <= *y && *y <= yRacketRight+rSize))){
      updateBallSpeed(true);
    }else{
      updateBallSpeed(false);
    }
  }
  //if there is no player left of the ball is on the racket then bounce
  if((yRacketLeft<0 && *x-1<1) or (yRacketLeft>=0 && *x-1<1 && (yRacketLeft <= *y && yRacketLeft+rSize >= *y))){
    *dx=-*dx;
    //speed increase
    if(*x-1<1 && ((yRacketLeft <= *y && *y <= yRacketLeft+1) or (yRacketLeft+rSize-1 <= *y && *y <= yRacketLeft+rSize))){
      updateBallSpeed(true);
    }else{
      updateBallSpeed(false);
    }
  }
}
void mooveRacket(){
  if(ard.pressed(UP_BUTTON) and yRacketLeft-rSpeed>0){
    yRacketLeft-=rSpeed;
  }
  if(ard.pressed(DOWN_BUTTON) and yRacketLeft+rSize<HEIGHT-1){
    yRacketLeft+=rSpeed;
  }
  
  if(ard.pressed(B_BUTTON) and yRacketRight-rSpeed>0){
    yRacketRight-=rSpeed;
  }
  if(ard.pressed(A_BUTTON) and yRacketRight+rSize<HEIGHT-1){
    yRacketRight+=rSpeed;
  }
}

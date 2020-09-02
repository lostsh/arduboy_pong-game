void game(){
  ard.clear();
  x+=dx;
  y+=dy;
  drawBall(x,y);
  drawWalls(true, true, true, false);
  drawRacket(yRacketLeft, -1, rSize);
  ard.display();
}
void settings(int *celerity, int *racketSize){  
}
void keyPressed(){
  if(ard.pressed(UP_BUTTON) and yRacketLeft>0){
    yRacketLeft-=rSpeed;
  }
  if(ard.pressed(DOWN_BUTTON) and yRacketLeft+rSize<HEIGHT-1){
    yRacketLeft+=rSpeed;
  }
  
  if(ard.pressed(B_BUTTON) and yRacketRight>0){
    yRacketRight-=rSpeed;
  }
  if(ard.pressed(A_BUTTON) and yRacketRight+rSize<HEIGHT-1){
    yRacketRight+=rSpeed;
  }
}

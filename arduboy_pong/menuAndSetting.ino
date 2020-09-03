void menu(){
  //=========================Main menu 
  ard.clear();
  ard.setCursor(30, 5);
  ard.setTextSize(3);
  ard.print(F("PONG"));
  ard.setTextSize(1.5);
  bool startPressed = false;
  while(!startPressed){
    ard.setCursor(32, 30);
    ard.print(F("PRESS START"));
    ard.display();
    startPressed = startBtnPressed(750);
    ard.setCursor(32, 30);
    ard.print(F("           "));
    ard.display();
    startPressed = startBtnPressed(700);
  }
  //========================Main menu end
  
  ard.setTextSize(1);
  ard.clear();
  ard.setCursor(30, 5);
  ard.setTextSize(3);
  ard.print(F("PONG"));
  ard.setTextSize(1);
  startPressed = false;
  bool userChooseToGoGame = true;
  while(!startPressed){
    
    //===========WHITE ON BLACK
    ard.setTextColor(WHITE);
    ard.setTextBackground(BLACK);
    //start rect
    ard.setCursor(12,42);
    ard.print(">START");
    ard.drawLine(11,41,11,50,BLACK);
    ard.drawLine(10,41,49,41,BLACK);
    ard.drawLine(48,41,48,50,BLACK);
    ard.drawRect(10,40,40,11, WHITE);
    //seting rect
    ard.setCursor(WIDTH-53,42);
    ard.print("SETING");
    ard.drawLine(WIDTH-54,41,WIDTH-54,50,BLACK);
    ard.drawLine(WIDTH-55,41,WIDTH-17,41,BLACK);
    ard.drawLine(WIDTH-17,41,WIDTH-17,50,BLACK);
    ard.drawRect(WIDTH-55,40,40,11, WHITE);
    ard.display();

    startPressed = startBtnPressed(250);

    //===========BLACK ON WHITE
    ard.setTextColor(BLACK);
    ard.setTextBackground(WHITE);
    if(userChooseToGoGame){
      //start rect
      ard.setCursor(12,42);
      ard.print(">START");
      ard.drawLine(11,41,11,50,WHITE);
      ard.drawLine(10,41,49,41,WHITE);
      ard.drawLine(48,41,48,50,WHITE);
      ard.drawRect(10,40,40,11, WHITE);
    }else{
      //seting rect
      ard.setCursor(WIDTH-53,42);
      ard.print("SETING");
      ard.drawLine(WIDTH-54,41,WIDTH-54,50,WHITE);
      ard.drawLine(WIDTH-55,41,WIDTH-17,41,WHITE);
      ard.drawLine(WIDTH-17,41,WIDTH-17,50,WHITE);
      ard.drawRect(WIDTH-55,40,40,11, WHITE);
    }
    ard.display();
    
    startPressed = startBtnPressed(200);

    //============
    if(ard.pressed(LEFT_BUTTON)){
      userChooseToGoGame = true;
    }
    if(ard.pressed(RIGHT_BUTTON)){
      userChooseToGoGame = false;
    }
    //============
  }
  ard.setTextColor(WHITE);
  ard.setTextBackground(BLACK);
  
  if(userChooseToGoGame){
    gameMode = 1;
  }else{
    gameMode = 2;
  }
}

bool startBtnPressed(const unsigned int waitTimeMs){
  for(int i=0;i<waitTimeMs;i++){
    if(ard.pressed(A_BUTTON) || ard.pressed(B_BUTTON)){
      delay(150);
      return true;
    }else{
      delay(1);
    }
  }
  return false;
}



void setting(int *cursorPosition, float *ballSpeed, float *racketSize, float *racketSpeed){
  mooveCursor(cursorPosition, 0, 3);
  ard.clear();
  ard.setCursor(7,0);
  ard.print(*ballSpeed);
  ard.print(" ");
  ard.print(*racketSize);
  ard.print(" ");
  ard.print(*racketSpeed);
  //=========================================ball speed
  if(*cursorPosition==3){
    updateValue(ballSpeed, MIN_BALL_SPEED, MAX_BALL_SPEED);
    setBallSpeed(*ballSpeed);//----------------------------------------------------just a test need improove
  }
  ard.drawLine(15, 10, 25, 10);
  ard.drawLine(20, 10, 20, HEIGHT-5);
  ard.drawLine(15, HEIGHT-5, 25, HEIGHT-5);
  int yValBallSpeed = map(*ballSpeed, MIN_BALL_SPEED, MAX_BALL_SPEED, 10, HEIGHT-5);
  ard.drawLine(18, yValBallSpeed, 22, yValBallSpeed);
  //=====================================end ball speed
  //=========================================racket size
  if(*cursorPosition==2){
    updateValue(racketSize, MIN_RACKET_SIZE, MAX_RACKET_SIZE);
  }
  ard.drawLine(35, 10, 45, 10);
  ard.drawLine(40, 10, 40, HEIGHT-5);
  ard.drawLine(35, HEIGHT-5, 45, HEIGHT-5);
  int yRacketSize = map(*racketSize, MIN_RACKET_SIZE, MAX_RACKET_SIZE, 10, HEIGHT-5);
  ard.drawLine(38, yRacketSize, 42, yRacketSize);
  //=====================================end racket size
  //========================================racket speed
  if(*cursorPosition==1){
    updateValue(racketSpeed, MIN_RACKET_SPEED, MAX_RACKET_SPEED);
  }
  ard.drawLine(55, 10, 65, 10);
  ard.drawLine(60, 10, 60, HEIGHT-5);
  ard.drawLine(55, HEIGHT-5, 65, HEIGHT-5);
  int yRacketSpeed = map(*racketSpeed, MIN_RACKET_SPEED, MAX_RACKET_SPEED, 10, HEIGHT-5);
  ard.drawLine(58, yRacketSpeed, 62, yRacketSpeed);
  //====================================end racket speed
  //===========================draw OK button
  ard.drawRect(WIDTH-15, HEIGHT-12, 15, 11);
  ard.setCursor(WIDTH-13, HEIGHT-10);
  ard.print(F("OK"));  
  bool okPressed = false;
  while(!okPressed && (*cursorPosition)==0){
    ard.setTextColor(WHITE);
    ard.setTextBackground(BLACK);
    ard.drawLine(WIDTH-14, HEIGHT-11, WIDTH-14, HEIGHT-3, BLACK);
    ard.drawLine(WIDTH-14, HEIGHT-11, WIDTH-1, HEIGHT-11, BLACK);
    ard.drawRect(WIDTH-15, HEIGHT-12, 15, 11);
    ard.setCursor(WIDTH-13, HEIGHT-10);
    ard.print(F("OK"));
    ard.display();
    okPressed = startBtnPressed(150);
    mooveCursor(cursorPosition, 0, 3);
    ard.setTextColor(BLACK);
    ard.setTextBackground(WHITE);
    ard.drawLine(WIDTH-14, HEIGHT-11, WIDTH-14, HEIGHT-3, WHITE);
    ard.drawLine(WIDTH-14, HEIGHT-11, WIDTH-1, HEIGHT-11, WHITE);
    ard.drawRect(WIDTH-15, HEIGHT-12, 15, 11);
    ard.setCursor(WIDTH-13, HEIGHT-10);
    ard.print(F("OK"));
    ard.display();
    okPressed = startBtnPressed(100);
    mooveCursor(cursorPosition, 0, 3);
  }
  ard.setTextColor(WHITE);
  ard.setTextBackground(BLACK);
  if(okPressed && *cursorPosition==0){//validate so goto menu
    gameMode = 0;
  }
  //============================END OK button
  ard.display();
}

void mooveCursor(int *cursorPointer, const int minVal, const int maxVal){
  if(ard.pressed(RIGHT_BUTTON) && *cursorPointer-1>=minVal){
    delay(190);
    (*cursorPointer)--;
  }
  if(ard.pressed(LEFT_BUTTON) && *cursorPointer+1<=maxVal){
    delay(190);
    (*cursorPointer)++;
  }
}

void updateValue(float *initValue, const float infVal, const float supVal){
  float pad = 0.05;
  if(ard.pressed(UP_BUTTON) && *initValue+pad<=supVal){
    delay(180);
    (*initValue)+=pad;
  }
  if(ard.pressed(DOWN_BUTTON) && *initValue-pad>=infVal){
    delay(180);
    (*initValue)-=pad;
  }
}

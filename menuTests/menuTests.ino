#include <Arduboy2.h>
Arduboy2 ard;

int bSpeed, rSpeed, rSize;
int settingCursor;
#define MAX_BALL_SPEED 50
#define MIN_BALL_SPEED 10
#define MAX_RACKET_SIZE 30
#define MIN_RACKET_SIZE 5
#define MAX_RACKET_SPEED 30
#define MIN_RACKET_SPEED 5

/**
 * 0 == Menu
 * 1 == Game
 * 2 == settings
 */
unsigned int gameMode;

void setup() {
  ard.begin();
  ard.setFrameRate(15);

  bSpeed = 40;
  rSpeed = 15;
  rSize = 10;
  gameMode = 0;
  settingCursor = 3;
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

void game(){
  ard.clear();
  ard.setCursor(0,0);
  ard.setTextWrap(true);
  ard.print("Gaming : Ball celrity is : ");
  ard.print(bSpeed);
  ard.print(" and racket size is : ");
  ard.print(rSize);
  ard.display();
  if(startBtnPressed(200)){
    gameMode = 0;
  }
}
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

void setting(int *cursorPosition, int *ballSpeed, int *racketSize, int *racketSpeed){
  mooveCursor(cursorPosition);
  ard.clear();
  ard.setCursor(0,0);
  ard.print("cursor value is : ");
  ard.print(*cursorPosition);
  ard.print("\n ball speed : ");
  ard.print(*ballSpeed);
  ard.print("\n racket size : ");
  ard.print(*racketSize);
  ard.print("\n racket speed : ");
  ard.print(*racketSpeed);
  //=========================================ball speed
  if(*cursorPosition==3){
    updateValue(ballSpeed, 20, 60);
  }
  //=====================================end ball speed
  //=========================================racket size
  if(*cursorPosition==2){
    updateValue(racketSize, 5, 30);
  }
  //=====================================end racket size
  //========================================racket speed
  if(*cursorPosition==1){
    updateValue(racketSpeed, 5, 30);
  }
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
    mooveCursor(cursorPosition);
    ard.setTextColor(BLACK);
    ard.setTextBackground(WHITE);
    ard.drawLine(WIDTH-14, HEIGHT-11, WIDTH-14, HEIGHT-3, WHITE);
    ard.drawLine(WIDTH-14, HEIGHT-11, WIDTH-1, HEIGHT-11, WHITE);
    ard.drawRect(WIDTH-15, HEIGHT-12, 15, 11);
    ard.setCursor(WIDTH-13, HEIGHT-10);
    ard.print(F("OK"));
    ard.display();
    okPressed = startBtnPressed(100);
    mooveCursor(cursorPosition);
  }
  ard.setTextColor(WHITE);
  ard.setTextBackground(BLACK);
  if(okPressed && *cursorPosition==0){//validate so goto menu
    gameMode = 0;
  }
  //============================END OK button
  ard.display();
}

void mooveCursor(int *cursorPointer){
  if(ard.pressed(RIGHT_BUTTON)){
    delay(180);
    (*cursorPointer)--;
  }
  if(ard.pressed(LEFT_BUTTON)){
    delay(180);
    (*cursorPointer)++;
  }
}

void updateValue(int *initValue, const int infVal, const int supVal){
  if(ard.pressed(UP_BUTTON) && *initValue+1<=supVal){
    delay(180);
    (*initValue)++;
  }
  if(ard.pressed(DOWN_BUTTON) && *initValue-1>=infVal){
    delay(180);
    (*initValue)--;
  }
}

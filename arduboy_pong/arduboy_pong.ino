#include <Arduboy2.h>
Arduboy2 ard;

float x=WIDTH/2, y=HEIGHT/2, dx, dy, Ybarre, Lbarre=15, Vbarre=0.2, Ybarre2;
int score;

bool jouer=false, gauche=false, towP=false, J2=false, mute=false;
int choix=25, mode=50;

BeepPin1 beep;

void setup(){
  ard.begin();
  beep.begin();//pour jouer un bip
  ard.setFrameRate(15);
  dx=-0.09;
  dy=0.1;
  score=0;
}
void loop(){
  if(jouer){
    jeux();
  }else{
    menu();
  }
}
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
void jeux(){
  if(towP){//jouer deux player
    ard.clear();
    //score
    x+=dx;
    y+=dy;
    balle(x,y);

    switch(score){
      case 2:
      dx-=0.001;
      dy+=0.001;
      break;
      case 5:
      dx-=0.01;
      dy+=0.01;
      break;
      case 8:
      dx-=0.1;
      dy+=0.1;
      break;
    }
    
    terrain(false,true);
    rebond(towP);
    barre(towP);
    gameOver();
    ard.display();
  }else{
    //jouer en signel player
    ard.clear();
    //le score
    ard.setCursor(25,HEIGHT/2-5);
    ard.print(F("Score : "));
    ard.print(score);
    //
    x=x+dx;
    y=y+dy;
    balle(x,y);
    rebond(towP);//ici towP sera faux donc un seul player
    terrain(false,false);
    barre(towP);//towP faux donc un seul joueur
    gameOver();
    
    ard.display();
  }
}
//---------------------------------------jeux-----------------------------------
void terrain(bool gauche,bool J2){
  ard.drawLine(0,0,WIDTH,0);//ligne du haut
  ard.drawLine(0,HEIGHT-1,WIDTH-1,HEIGHT-1);//ligne du bas
  if(gauche){
    ard.drawLine(0,0,0,HEIGHT-1);//ligne gauche
  }
  if(!J2){
    ard.drawLine(WIDTH-1,0,WIDTH-1,HEIGHT-1);//ligne droite
  }
  if(J2){
    for(int i=0;i<=HEIGHT;i++){
      ard.drawLine(WIDTH/2,0,WIDTH/2,i);
    }
  }
}
void balle(int x,int y){
  //la balle est constitue de trois traits de longeut trois
  ard.drawLine(x-1,y-1,x-1,y+1);//gauhe
  ard.drawLine(x,y-1,x,y+1);//milieu
  ard.drawLine(x+1,y-1,x+1,y+1);//droite
}
void barre(bool towP){
  ard.drawLine(0,Ybarre,0,Ybarre+Lbarre);
  ard.drawLine(1,Ybarre,1,Ybarre+Lbarre);
  if(ard.pressed(UP_BUTTON) and Ybarre>0){
    Ybarre-=Vbarre;
  }
  if(ard.pressed(DOWN_BUTTON) and Ybarre+Lbarre<HEIGHT-1){
    Ybarre+=Vbarre;
  }
  if(towP){
    ard.drawLine(WIDTH-1,Ybarre2,WIDTH-1,Ybarre2+Lbarre);
    ard.drawLine(WIDTH-2,Ybarre2,WIDTH-2,Ybarre2+Lbarre);
    if(ard.pressed(B_BUTTON) and Ybarre2>0){
      Ybarre2-=Vbarre;
    }
    if(ard.pressed(A_BUTTON) and Ybarre2+Lbarre<HEIGHT-1){
      Ybarre2+=Vbarre;
    }
  }
}
void rebond(bool TowPlayerGame){
  if(x+1>WIDTH-1 and !TowPlayerGame){
    dx=-dx;
  }
  if(y+1>HEIGHT-1 or y-1<1){
    dy=-dy;
  }
  //la raquette
  if((x-1<=2)and(y+1>=Ybarre and y-1<=Ybarre+Lbarre)){
    dx=-dx;
    if(!TowPlayerGame){
      score++;
    }
    //ci dessou le bip
    if(!mute){
      beep.tone(beep.freq(1000));
      ard.delayShort(30);
      beep.noTone();
    }
  }
  if(TowPlayerGame){
    if(x+1>WIDTH-2 and (y+1>=Ybarre2 and y-1<=Ybarre2+Lbarre)){
      dx=-dx;
      //ci dessou le bip
      if(!mute){
        beep.tone(beep.freq(1000));
        ard.delayShort(30);
        beep.noTone();
      }
    }
  }
  /*
  //les bord de la raquette
  if((x-1<=2)and((y-1>=Ybarre and y+1<=Ybarre+2)or(y-1>=Ybarre+Lbarre-2 and y+1<=Ybarre+Lbarre))){
    dx=-dx+0.01;
    score++;
    //ci dessou le bip
    beep.tone(beep.freq(1000));
    ard.delayShort(30);
    beep.noTone();
  }
  */
}
void gameOver(){
  if(!towP){
    if(x-1<0){
      //setup();
      ard.clear();
      ard.setCursor(40,HEIGHT/2-5);
      ard.print(F("-GAME OVER-"));
      ard.setCursor(40,HEIGHT/2+5);
      ard.print(F("Score :"));
      ard.print(score);
      ard.display();
      delay(2000);
      jouer=false;
      x=WIDTH/2;
      dx=-0.09;
      dy=0.1;
      //score=0;
    }
  }
  
  if(towP){
    if(x<0){
      ard.clear();
      ard.setCursor(40,HEIGHT/2-5);
      ard.print(F("GAME OVER"));
      ard.setCursor(40,HEIGHT/2+5);
      ard.print(F("Player 1"));
      jouer=false;
      ard.display();
      delay(1500);
      x=WIDTH/2;
      y=HEIGHT/2;
    }
    if(x>WIDTH-1){
      ard.clear();
      ard.setCursor(10,HEIGHT/2-5);
      ard.print(F("GAME OVER"));
      ard.setCursor(10,HEIGHT/2+5);
      ard.print(F("Player 2"));
      jouer=false;
      ard.display();
      delay(1500);
      x=WIDTH/2;
      y=HEIGHT/2;
    }
  }
}
//---------------------------------------------menu-------------------------------------
void menu(){
  ard.clear();
  if(score!=0){
    ard.setCursor(45,55);
    ard.print("Score :");
    ard.print(score);
  }
  terrain(true,false);
  ard.setCursor(50,10);
  ard.print(F("P0NG"));
  ard.setCursor(20,25);
  ard.print(F("Level :"));
  for(int i=0;i<=5;i++){
    ard.setCursor(15*i+15,40);
    ard.print(i);
  }
  //--------------pitit fleche indique les lvl-------------
  ard.drawLine(102,42,107,42);
  ard.drawLine(103,41,103,43);
  //-------------------------------------------------------
  
  //====================fleche de selection==================
  ard.drawLine(choix-8,mode,choix-8,mode);
  ard.drawLine(choix-9,mode+1,choix-7,mode+1);
  ard.drawLine(choix-10,mode+2,choix-6,mode+2);
  //=========================================================
  
  if(mode==50){
    if(ard.pressed(LEFT_BUTTON) and choix>25){
    choix-=15;
    delay(350);
    }
    if(ard.pressed(RIGHT_BUTTON) and choix<105){
      choix+=15;
      delay(350);
      }
  }
  
  ard.setCursor(80,20);
  ard.print(F("2Player"));
  
  if(choix>105){
    if(ard.pressed(UP_BUTTON) and mode>30){
      mode-=20;
      delay(300);
    }
    if(ard.pressed(DOWN_BUTTON) and mode<50){
      mode+=20;
      delay(300);
    }
  }

  if(ard.pressed(B_BUTTON)){
    mute=!mute;
  }
  
  //les lvl
  towP=false;
  if(ard.pressed(A_BUTTON)){
    score=0;
    switch(choix){
      case 25:
      ard.setCursor(50,35);
      ard.print(F("Go game"));
      delay(500);
      dx=-0.09;
      dy=0.1;
      Vbarre=0.2;
      Lbarre=15;
      jouer=true;
      break;
      case 25+15:
      ard.setCursor(50,35);
      ard.print(F("Go game"));
      delay(500);
      dx=-0.1;
      dy=0.2;
      Vbarre=0.25;
      Lbarre=15;
      jouer=true;
      break;
      case 25+2*15:
      ard.setCursor(50,35);
      ard.print(F("Go game"));
      delay(500);
      dx=-0.199;
      dy=0.3;
      Vbarre=0.29;
      Lbarre=15;
      jouer=true;
      break;
      case 25+3*15:
      ard.setCursor(50,35);
      ard.print(F("Go game"));
      delay(500);
      dx=0.24;
      dy=-0.399;
      Vbarre=0.299;
      Lbarre=15;
      jouer=true;
      break;
      case 25+4*15:
      jouer=false;
      ard.setCursor(50,35);
      ard.print(F("Go game"));
      delay(500);
      dx=0.299;
      dy=0.4;
      Vbarre=0.4;
      Lbarre=15;
      jouer=true;
      break;
      case 25+5*15:
      jouer=false;
      ard.setCursor(50,35);
      ard.print(F("Go game"));
      delay(500);
      dx=0.35;
      dy=0.55;
      Lbarre=20;
      Vbarre=0.49;
      jouer=true;
      break;
    }
    if(mode==30){
      x=WIDTH/2-1;
      y=HEIGHT/2-1;
      dx=-0.25;
      dy=0.3;
      Lbarre=15;
      Vbarre=0.3;
      towP=true;
      jouer=true;
      //jeux(true);
    }
  }
  ard.display();
  //return jouer;
}


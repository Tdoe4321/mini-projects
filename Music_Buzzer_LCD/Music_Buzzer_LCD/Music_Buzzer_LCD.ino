#include <LiquidCrystal.h>
#include "pitches.h"

LiquidCrystal lcd(12, 11, A0, A1, A2, A3, 5, 4, 3, 2);

int randomNum = 0;
unsigned long textTime = 0;
unsigned long noteTime = 0;
unsigned long blankTime = 0;
unsigned long now = 0;
int thisNote = 0;
boolean blank = false;
boolean midNote = false;
int noteDuration = 0;
int lastRand = -1;


int melody[] = {
  NOTE_CS3, NOTE_GS3, NOTE_CS4, NOTE_B3, NOTE_AS3, NOTE_GS3, NOTE_AS3, NOTE_GS3, NOTE_FS3, NOTE_GS3,
  0,
  NOTE_CS3, NOTE_GS3, NOTE_CS4, NOTE_B3, NOTE_AS3, NOTE_GS3, NOTE_AS3, NOTE_GS3, NOTE_FS3, NOTE_GS3,
  0,
  NOTE_GS3, NOTE_CS3, NOTE_G3, NOTE_GS3, NOTE_AS3, NOTE_GS3, NOTE_F3, NOTE_CS3, NOTE_G3, NOTE_GS3, NOTE_AS3, NOTE_GS3,
  NOTE_DS3, NOTE_DS4, NOTE_DS4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_DS4,
  NOTE_CS4, NOTE_FS3, NOTE_C4, NOTE_CS4, NOTE_DS4, NOTE_CS4, NOTE_AS3, NOTE_FS3,
  NOTE_C4, NOTE_CS4, NOTE_DS4, NOTE_CS4, NOTE_GS3, NOTE_CS4, NOTE_GS4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_GS4,
  0
  
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  2, 1, 2, 1, 8, 8, 4, 2, 2, 1,
  2,
  2, 1, 2, 1, 8, 8, 4, 2, 2, 1,
  1,
  2, 2, 1, 8, 8, 4, 4, 4, 2, 8, 8, 4,
  4, 4, 2, 2, 8, 8, 1,
  2, 2, 2, 4, 4, 6, 6, 6,
  4, 8, 8, 4, 4, 4, 4, 4, 4, 8, 8, 1,
  1
  
  
};

void setup() {
  pinMode(6, OUTPUT);
  analogWrite(6, 40);

  randomSeed(analogRead(5));
  
  lcd.begin(8, 2); 
  lcd.print("Hello, R");
  lcd.setCursor(0, 1);
  lcd.print("achel!");
  delay(2000);
}

void loop() { 
  randomNum = random(1,10);
  if(randomNum == lastRand){
    randomNum = random(1, 10);
    if(randomNum == lastRand){
      randomNum = random(1, 10);
    }
  }
  lastRand = randomNum;

  switch(randomNum){
    case 1: print8x2("                Roads? Where we're going, we don't need roads! ");
      break;
    case 2: print8x2("                Woah. This is heavy. ");
      break;
    case 3: print8x2("                You built a time machine...out of a DeLorean? ");
      break;
    case 4: print8x2("                Calvin Klein? It's written all over your underwear. ");
      break;
    case 5: print8x2("                McFly! ");
      break;
    case 6: print8x2("                Why don't you make like a tree, and get out of here? ");
      break;
    case 7: print8x2("                What are you looking at, butthead? ");
      break;
    case 8: print8x2("                Great Scott! ");
      break;
    case 9: print8x2("                Manure! I hate manure! ");
      break;
  }
}

void print8x2(String text){
  int len = text.length();
  for(int i = 0; i < (len); i ++){
    textTime = millis();
    now = millis();
    while(now - textTime < 200){
      now = millis();
      playMusic();
    }
    lcd.setCursor(0,0);
    lcd.print(getTop(text));
    lcd.setCursor(0,1);
    lcd.print(getBottom(text));
    text = text.substring(1);
  }
}

String getTop(String text){
  String topRet = "";  
  topRet = text.substring(0,8);
  return topRet;
}

String getBottom(String text){
  String botRet = "";
  botRet = text.substring(8, 16);
  return botRet;
}

void playMusic(){
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  if(!midNote){
    noteDuration = 1000 / noteDurations[thisNote] / 1.75;
    if(melody[thisNote] != 0){
      tone(9, melody[thisNote]);
    }
    else {
      noTone(9);
    }
    noteTime = millis();
    blankTime = millis();
    midNote = true;
  }
  
  if(!blank){
    if(now - noteTime > noteDuration){
      thisNote++;
      if(thisNote >= 62){
        thisNote = 0;
      }
      blank = true;
      midNote = false;
    }
  }
  else if(blank){
    noTone(9);
    if(now - blankTime > ((1000 / noteDurations[thisNote-1]) * .5)){
      blank = false;
      midNote = false;
    }
  }

}


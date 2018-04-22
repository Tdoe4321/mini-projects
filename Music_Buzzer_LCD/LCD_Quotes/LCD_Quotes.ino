#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, A0, A1, A2, A3, 5, 4, 3, 2);

int randomNum = 0;

void setup() {
  pinMode(6, OUTPUT);
  analogWrite(6, 45);

  randomSeed(analogRead(5));
  
  lcd.begin(8, 2); 
  lcd.print("Hello, R");
  lcd.setCursor(0, 1);
  lcd.print("achel!");
  delay(2000);
}

void loop() { 
  randomNum = random(1,10);

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
    lcd.setCursor(0,0);
    lcd.print(getTop(text));
    lcd.setCursor(0,1);
    lcd.print(getBottom(text));
    text = text.substring(1);
    delay(150);
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


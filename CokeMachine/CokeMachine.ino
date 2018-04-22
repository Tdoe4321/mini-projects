#include <Bounce2.h>

const int CAFFREE = 9;
const int SPRITEZERO = 8;
const int COKE = 7;
const int SPRITE = 6;
const int DIETCOKE = 5;
const int FANTA = 4;
const int COKEZERO = 3;
const int MAG = 2;
const int VEND = 13;

//Declares an array of 7 Bounces called debouncer
Bounce debouncer[7] = {Bounce()};

byte bState[7] = {0,0,0,0,0,0,0};
byte bLastState[7] = {0,0,0,0,0,0,0};

byte count = 0;
byte guess[7];
const byte combination[] = {2,7,4,1,6,3,5};
bool flag;

unsigned long previousMillis = 0;

void setup() {
Serial.begin(9600);

pinMode(CAFFREE, INPUT);
pinMode(SPRITEZERO, INPUT);
pinMode(COKE, INPUT);
pinMode(SPRITE, INPUT);
pinMode(DIETCOKE, INPUT);
pinMode(FANTA, INPUT);
pinMode(COKEZERO, INPUT);

pinMode(MAG, OUTPUT);
pinMode(VEND,OUTPUT);

//This attached the coke products to the debouncer array. It also sets the bounce interval to 15ms
debouncer[0].attach(CAFFREE);
debouncer[0].interval(20);
debouncer[1].attach(SPRITEZERO);
debouncer[1].interval(20);
debouncer[2].attach(COKE);
debouncer[2].interval(20);
debouncer[3].attach(SPRITE);
debouncer[3].interval(20);
debouncer[4].attach(DIETCOKE);
debouncer[4].interval(20);
debouncer[5].attach(FANTA);
debouncer[5].interval(20);
debouncer[6].attach(COKEZERO);
debouncer[6].interval(20);
}

void loop() {
  //This is used for the VEND check - It allows for the program to keep running, but also reset the puzzle
  if(millis() - previousMillis >= 300){
    digitalWrite(MAG,HIGH);
    digitalWrite(VEND,HIGH); 
  }

//Updates debouncer and puts current voltage into bState array  
for(int j = 0; j <=6; j++){
    debouncer[j].update();
    bState[j] = debouncer[j].read();
}

//Checks current button presses 
for(int i = 0; i <=6; i++ ){
  if(bState[i] != bLastState[i]){
      if(bState[i] == LOW){
      guess[count] = i+1;
      count++;
      Serial.print(i+1);
      if(i == 2){
        digitalWrite(VEND,LOW);
        previousMillis = millis();
        }
      }
    }
    bLastState[i] = bState[i];
  }

//  Serial.print(guess[0]);  
//  Serial.print(guess[1]);
//  Serial.print(guess[2]);
//  Serial.print(guess[3]);
//  Serial.print(guess[4]);
//  Serial.print(guess[5]);
//  Serial.println(guess[6]);

//Checks current code input, resets if incorect 
for(int n = 0; n <= count-1; n++){
  flag = true;
  if(guess[n] != combination[n]){
    flag = false;
    count = 0;
    if(guess[n] == 2){
      count++;
    }
  }
}

//Checks whole code when there are 7 numbers entered
if(flag && (count >= 7)){
  digitalWrite(MAG,LOW);  
  delay(300);
  count = 0;
  }
}

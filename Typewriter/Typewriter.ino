#include <Bounce2.h>

//num is the number of letters used in the code word, EX HELP = 4, HELLO = 4
const int num = 4;

//Change pin numbers
const int H = 6;
const int E = 7;
const int L = 8;
const int P = 9;
const int MAG = 13;

//Declares an array of 'num' Bounces called debouncer
Bounce debouncer[num] = {Bounce()};

byte bState[num] = {0};
byte bLastState[num] = {0};

byte count = 0;
//Change 'numComb' to the number of characters your code is, EX HELP = 4, HELLO = 5
const int numComb = 4;
byte guess[numComb] = {0};
const byte combination[numComb] = {1,2,3,4}; // This code cooresponds to the numbers that you set later in the debouncer.attach area
bool flag;

void setup() {
Serial.begin(9600);

pinMode(H, INPUT);
pinMode(E, INPUT);
pinMode(L, INPUT);
pinMode(P, INPUT);

pinMode(MAG, OUTPUT);

//This attaches the letters to the debouncer array. It also sets the bounce interval to 20ms
debouncer[0].attach(H);     // these letters now correspond to the combination, EX H = 1, E = 2, L = 3, P = 4
debouncer[0].interval(20);
debouncer[1].attach(E);
debouncer[1].interval(20);
debouncer[2].attach(L);
debouncer[2].interval(20);
debouncer[3].attach(P);
debouncer[3].interval(20);
}

void loop() {
  digitalWrite(MAG,HIGH);
  
//Updates debouncer and puts current voltage into bState array  
for(int j = 0; j < num; j++){
    debouncer[j].update();
    bState[j] = debouncer[j].read();
}

//Checks current button presses 
for(int i = 0; i < num; i++ ){
  if(bState[i] != bLastState[i]){
    if(bState[i] == LOW){
      guess[count] = i+1;
      count++;
      Serial.print(i+1);
      }
    }
  bLastState[i] = bState[i];
}

/*  Serial.print(guess[0]);  
    Serial.print(guess[1]);
    Serial.print(guess[2]);
    Serial.print(guess[3]);
    Serial.print(guess[4]);
    Serial.print(guess[5]);
    Serial.println(guess[6]);  */

//Checks current code input, resets if incorect 
for(int n = 0; n <= count-1; n++){
  flag = true;
  if(guess[n] != combination[n]){
    flag = false;
    count = 0;
    //Ok, so right here is super important. If the code is H-E-L-P, and the user has entered H-E, but then decides to enter
    //another 'H' the code resets, putting the 'count' of correct numbers back to '0' , but in actuality they have enterd the correct
    //letter for the start of the code, so right here it pulls the count up to 1 if they entered the number of the first letter
    //Which means that you need to make sure that this number = whatever number cooresponds to the first letter of the code
    if(guess[n] == 1){
      count++;
    }
  }
}

//Checks whole code when there are 'num' numbers entered
  if(flag && (count >= numComb)){
    digitalWrite(MAG,LOW);  
    delay(300);
    count = 0;
  }
}

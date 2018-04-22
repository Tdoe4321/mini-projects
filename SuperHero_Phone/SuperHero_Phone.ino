/*  Code:SuperHero_PHONE3
 *  By: Tyler Gragg
 *  Date: 7/8/2017
 *  For: Practical Low Voltage Solutions
 *  Version: 1.0
 *  
 *  This code is designed to unlock a maglock when a specific phone number is entered into the keypad. If either the '*' key or the '#' key is pressed, it resets the user input.
 *  Also, if the user waits more than 10 seconds between inputs, the code is reset.
 */

#include <Keypad.h>
 
const char secretNumber[] = {'4','0','4','6','7','2','3','9', '1', '8'}; //defines for phonenumbers
char inputNumber[] = {'A','A','A','A','A','A','A','A','A','A' };
int codePosition= 0;

int resetTime = 10000; //time reseting
long lastPress = 0;

char key;   //key for recording current key

int magPin = A0;
 
const byte rows = 4;
const byte cols = 3;
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
 
byte rowPins[rows] = {5, 4, 3, 2};
byte colPins[cols] = {8, 7, 6};
 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);
 
 
void setup(){
  pinMode(magPin, OUTPUT);  //Sets mag pin for relay
  pinMode(magPin, LOW);
  Serial.begin(9600);
}
 
void loop(){
  digitalWrite(magPin, LOW);
  
  key = keypad.getKey();
  // check if a key is pressed, then inputs key ino our code
  if(key != NO_KEY && keypad.getState() == PRESSED){
    inputNumber[codePosition] = key;
    codePosition++;
 
    if (codePosition> 9){
      resetCode();
        }
    lastPress== millis();
    }
    
  if( checkCode() == true){
    Serial.println( " TRUE TRUE TRUE");
    digitalWrite(magPin, HIGH);
    delay(5000);
  }
    
  //section for resetting code if '#' is pressed, or if too much time passes.
  if( key== '#' || key == '*'){
   resetCode();
  }
  if(millis() - lastPress > resetTime){
    resetCode();
  }
  
  
  //serial section for debugging
  if(key){
        Serial.println(key);
        Serial.println("CurrentCode = ");
        for(int x = 0; x<=9; x++){
          Serial.print(inputNumber[x]);
        }
        Serial.println();
        Serial.print( "Current position = ");
        Serial.println(codePosition);
      }

    
  delay(10);
}

// reset code is called to reset the input code
void resetCode(){
  for(int i =0; i<10; i++){
    inputNumber[i] = 'A';
    codePosition = 0;
  }
}


// Function Check code checks each position, and if all true, returns true
boolean checkCode(){
  if(checkPosition(0) && checkPosition(1) && checkPosition(2) && checkPosition(3) && 
     checkPosition(4) && checkPosition(5) && checkPosition(6) && checkPosition(7) &&
     checkPosition(8) && checkPosition(9)){
    return true;
  }
  else{
    return false;
  }
}
 
// Function  check position checks a single position of code for true/false   
boolean checkPosition(int pos){
  if(inputNumber[pos]== secretNumber[pos]){
    
    Serial.print( " True at ");
    Serial.println(pos);
    
    return true;
  }
  else{
    return false;
  }
}  

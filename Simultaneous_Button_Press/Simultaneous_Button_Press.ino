/*  Code: MomentarySwitch
 *  By: Tyler Gragg
 *  Date: 6/24/2017
 *  For: Practical Low Voltage Solutions
 *  Version: 1.3
 *  
 *  This code is designed to trigger a relay when three momentary switches are pressed simultaneously.
 *  Because of the circuitry of the relay, it requires an "always on" to be closed and when it recieves a LOW, it will open the relay.
 */

#define str 8 // Start input pin
#define b1 5 // Button 1 pin
#define b2 6 // Button 2 pin 
#define b3 7 // Button 3 pin

#define l1 2
#define l2 3
#define l3 4

#define relay 11 // Relay pin

int start = 0; // Start state

int bstate1 = 0; // Button States
int bstate2 = 0;
int bstate3 = 0;

boolean flag1 = false; // flag for all buttons
boolean flag2 = false;
boolean flag3 = false;

boolean stFlag = false; // flag for start state

unsigned long t1 = 0; // time of button pressed
unsigned long t2 = 0;
unsigned long t3 = 0;

unsigned long stTime = 0; // counts to 60 for the purpose of allowing the keys to turn
unsigned long curTime = 60000;  // Compare this to stTime for allowing the keys to turn

long t = 1000; // Sets max time difference for the pressed (1500 = 1.5 seconds)

void setup() {
  pinMode(b1, INPUT); // Pin setups
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);

  pinMode(str, INPUT);

  pinMode(l1, OUTPUT);  // LED setups
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);

  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(l3, LOW);
  
  pinMode(relay, OUTPUT);  
  digitalWrite(relay, HIGH); // Start the relay with sending out a HIGH value

  Serial.begin(9600);
}

void relayCall(){
  digitalWrite(relay, LOW); // Set relay to LOW
  Serial.print("Open on up!");
  delay(60000); // Wait for 60 seconds
  digitalWrite(relay, HIGH); // Set relay back to HIGH 
}

void loop() {
  curTime = max(millis(), curTime); // gets current time and stores it. 
                                    // if within 60 seconds of the start, sets the current time to 60 seconds
  
  bstate1 = digitalRead(b1); //read current button states
  bstate2 = digitalRead(b2);
  bstate3 = digitalRead(b3);

  start = digitalRead(str);

  if(start == HIGH){
    if(stFlag == false){
      stTime = millis(); // get start time
    }
    stFlag = true;  // used for reseting time 
  }
  else{
    stFlag = false;
  }
  
  if(bstate1 == HIGH){
    if(flag1 == false){
      t1 = millis(); // get current time of press
    }
    flag1 = true; 
  }
  
  else{ //reset
    t1 = 0;
    flag1 = false;
  }

  if(bstate2 == HIGH){
    if(flag2 == false){
      t2 = millis(); // get current time of press
    }
    flag2 = true;
  }
  
  else{ //reset
    t2 = 0;
    flag2 = false;
  }

  if(bstate3 == HIGH){
    if(flag3 == false){
      t3 = millis(); // get current time of press
    }
    flag3 = true;
  }
  
  else{
    t3 = 0; //reset 
    flag3 = false;
  }
  
  if(curTime - stTime < 60000){ // if the time between the start and now is less than 60 seconds...
    digitalWrite(l1, HIGH);  // Turn on LEDs
    digitalWrite(l2, HIGH);
    digitalWrite(l3, HIGH);
    if(((abs(t1-t2) < t) || (abs(t2-t1) < t)) && ((abs(t2-t3) < t) || (abs(t3-t2) < t)) && ((abs(t1-t3) < t) || (abs(t3 - t1) < t))){ // if all three buttons are within 't' seconds of each other...
      if(flag1 && flag2 && flag3){ // if all three are currently pressed...
        relayCall(); // call the relay function
      }
    }
  }

  else(){
    digitalWrite(l1, LOW);  // Turn off LEDs
    digitalWrite(l2, LOW);
    digitalWrite(l3, LOW);
  }

  Serial.print("t1 = ");
  Serial.print(t1);
  Serial.print(" t2 = ");
  Serial.print(t2);
  Serial.print(" t3 = ");
  Serial.println(t3);
}

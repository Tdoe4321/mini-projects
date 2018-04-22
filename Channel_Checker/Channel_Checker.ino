int ch1 = 0;
int ch2 = 0;
int ch3 = 0;
int ch4 = 0;


void setup() {
  
  Serial.begin(9600);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A2, INPUT);
  pinMode(8, INPUT);

  
}

void loop() {
  ch1 = pulseIn(A4, HIGH, 250000);
  ch2 = pulseIn(A5, HIGH, 250000);
  ch3 = pulseIn(A2, HIGH, 250000);
  //ch4 = pulseIn(8, HIGH, 250000);

  Serial.print("Left Stick: X:\t");  
  //ch4 = map(ch4, 994, 1986, -500, 500);
  if(ch4 > -23 && ch4 < 23)
    ch4 = 0;
  Serial.print(ch4);        
  //Serial.print(ch4);
  
  Serial.print("\tY:\t"); 
  ch3 = map(ch3, 1002, 1986, -500, 500);
  if(ch3 > -100 && ch3 < 100)
    ch3 = 0;
  Serial.print(ch3);        
  //Serial.print(ch3);
  
  Serial.print("\tRight Stich X:\t");
  ch1 = map(ch1, 986, 1970, -500, 500);
  if(ch1 > -23 && ch1 < 23)
    ch1 = 0;
  Serial.print(ch1);
  //Serial.print(ch1);
  
  Serial.print("\tY:\t");
  ch2 = map(ch2, 987, 1970, -500, 500);
  if(ch2 > -23 && ch2 < 23)
    ch2 = 0;
  Serial.println(ch2);
  //Serial.println(ch2);
  
  
  //delay(100);

  
}

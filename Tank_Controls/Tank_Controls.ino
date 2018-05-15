/*  Code: Tank_Controls
*   Version: 1.5
*   By: Tyler Gragg
*   Date: 6/25/2017
*   For: Personal Project
*
*   This code is designed to control a pusher battlebot for dragoncon 2017. The idea for this code is that is reads in values from a reciever and sends them out to an H-Bridge that controls four motors spinning
*   bi-directionally. The code also has a section that will flip the controls in case the robot gets flipped upside down.
*/

#define controlPin1A 3  // 4 pins used for spinning motors in specific directions
#define controlPin1B 2  
#define controlPin2A 12
#define controlPin2B 13

#define enableRight 11  // 2 pins used to select speed for motors
#define enableLeft 5

#define channel1 A5 // rc input
#define channel2 A4

#define flipflop A2 // switch controls input

int motorEnabled = 0;     // values for turning on system
int motor1Direction = 0;  // direction for motors
int motor2Direction = 0;

int skipTime = 0;        // down time for changing spin direction

int flipVal = 0; // used to flip controls

int ch1;  // input from reciever
int ch2;  // input from reciever

void setup() {
	Serial.begin(9600);
	pinMode(channel1, INPUT); // channel 1 RC
	pinMode(channel2, INPUT); // channel 2 RC

	pinMode(controlPin1A, OUTPUT);  // direction pins
	pinMode(controlPin1B, OUTPUT);
	pinMode(controlPin2A, OUTPUT);
	pinMode(controlPin2B, OUTPUT);

	pinMode(enableRight, OUTPUT);   // speed pins
	pinMode(enableLeft, OUTPUT);

	pinMode(flipflop, INPUT); // direction flipper

	analogWrite(enableRight, 0);    // initial speed setting
	analogWrite(enableLeft, 0);
}

// Turn right motor foreword
void rightF() {
	if (motor1Direction != 1) {
		digitalWrite(controlPin1A, LOW);
		digitalWrite(controlPin1B, LOW);
		delay(skipTime);
	}
	digitalWrite(controlPin1A, HIGH);
	digitalWrite(controlPin1B, LOW);
	motor1Direction = 1;
}

// Turn left motor foreword
void leftF() {
	if (motor2Direction != 1) {
		digitalWrite(controlPin2A, LOW);
		digitalWrite(controlPin2B, LOW);
		delay(skipTime);
	}
	digitalWrite(controlPin2A, LOW);
	digitalWrite(controlPin2B, HIGH);
	motor2Direction = 1;
}

// Turn right motor backword
void rightB() {
	if (motor1Direction != 0) {
		digitalWrite(controlPin1A, LOW);
		digitalWrite(controlPin1B, LOW);
		delay(skipTime);
	}
	digitalWrite(controlPin1A, LOW);
	digitalWrite(controlPin1B, HIGH);
	motor1Direction = 0;
}

// Turn left motor backword
void leftB() {
	if (motor2Direction != 0) {
		digitalWrite(controlPin2A, LOW);
		digitalWrite(controlPin2B, LOW);
		delay(skipTime);
	}
	digitalWrite(controlPin2A, HIGH);
	digitalWrite(controlPin2B, LOW);
	motor2Direction = 0;
}

//Reads in from the reciever and pumps out a value between -255 and 255 for all the channels
void readVals() {
	ch2 = pulseIn(channel1, HIGH, 250000);  // input from channel
	ch1 = pulseIn(channel2, HIGH, 250000);  // input from channel
	flipVal = pulseIn(flipflop, HIGH, 250000); // input from switch

	ch1 = map(ch1, 1000, 2000, -255, 255);  // remap the values to ones the H-bridge cares about
	ch2 = map(ch2, 1000, 2000, -255, 255);
	flipVal = map(flipVal, 1000, 2000, -255, 255);

	if (ch1 > 300 || ch1 < -300) {  // invalid input reset
		ch1 = 0;
	}
	if (ch2 > 300 || ch2 < -300) {
		ch2 = 0;
	}
	if (flipVal > 300 || flipVal < -300) {
		flipVal = 0;
	}

	ch1 = constrain(ch1, -255, 255); // Constrain values max and min
	ch2 = constrain(ch2, -255, 255);
	flipVal = constrain(flipVal, -255, 255);

	if (ch1 >= -15 && ch1 <= 15) { // widen the midpoint values
		ch1 = 0;
	}
	if (ch2 >= -15 && ch2 <= 15) {
		ch2 = 0;
	}
}

void motorDirection() {
	if (flipVal >= 0) { // Right side up controls
		if (ch2 > 100) {
			rightF();
			leftB();
		}
		else if (ch2 < -100) {
			rightB();
			leftF();
		}
		
		else if (ch1 > 0) {     // move foreward
			rightB();
			leftB();
		}

		else if (ch1 < 0) { // move backward
			rightF();
			leftF();
		}

		else {
			digitalWrite(controlPin1A, LOW);
			digitalWrite(controlPin1B, LOW);
			digitalWrite(controlPin2A, LOW);
			digitalWrite(controlPin2B, LOW);
		}
	}


	else if (flipVal < 0) { // upside down controls
		if (ch2 > 100) {
			rightF();
			leftB();
		}
		else if (ch2 < -100) {
			rightB();
			leftF();
		}

		else if (ch1 > 0) {     // move foreward
			rightF();
			leftF();
		}

		else if (ch1 < 0) { // move backward
			rightB();
			leftB();
		}

		else {
			digitalWrite(controlPin1A, LOW);
			digitalWrite(controlPin1B, LOW);
			digitalWrite(controlPin2A, LOW);
			digitalWrite(controlPin2B, LOW);
		}
	}
}

void spinMotors() {

	if (motorEnabled == 1) {
		digitalWrite(enableLeft, HIGH);
		digitalWrite(enableRight, HIGH);
	}

	else {
		digitalWrite(enableLeft, LOW);
		digitalWrite(enableRight, LOW);
	}
}

void loop() {
	readVals();

	motorDirection();

	if (ch1 != 0 || ch2 != 0) { // turn system on
		motorEnabled = 1;
	}
	else {
		motorEnabled = 0;
	}

	spinMotors();

	Serial.print("CH1 = ");
	Serial.print(ch1);
	Serial.print("   CH2 = ");
	Serial.println(ch2);
}
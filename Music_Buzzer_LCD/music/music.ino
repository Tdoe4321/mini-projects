/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_CS3, NOTE_GS3, NOTE_CS4, NOTE_B3, NOTE_AS3, NOTE_GS3, NOTE_AS3, NOTE_GS3, NOTE_FS3, NOTE_GS3,
  0,
  NOTE_CS3, NOTE_GS3, NOTE_CS4, NOTE_B3, NOTE_AS3, NOTE_GS3, NOTE_AS3, NOTE_GS3, NOTE_FS3, NOTE_GS3,
  0,
  NOTE_GS3, NOTE_CS3, NOTE_G3, NOTE_GS3, NOTE_AS3, NOTE_GS3, NOTE_F3, NOTE_CS3, NOTE_G3, NOTE_GS3, NOTE_AS3, NOTE_GS3,
  NOTE_DS3, NOTE_DS4, NOTE_DS4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_DS4,
  NOTE_CS4, NOTE_FS3, NOTE_C4, NOTE_CS4, NOTE_DS4, NOTE_CS4, NOTE_AS3, NOTE_FS3,
  NOTE_C4, NOTE_CS4, NOTE_DS4, NOTE_CS4, NOTE_GS3, NOTE_CS4, NOTE_GS4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_GS4
  
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
  4, 8, 8, 4, 4, 4, 4, 4, 4, 8, 8, 1
  
  
};

void setup() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 61; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(9, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(9);
  }
}

void loop() {
  
}

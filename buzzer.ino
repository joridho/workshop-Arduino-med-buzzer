#include <Keypad.h>
#include "songs.h"

// change this to make the song slower or faster
byte tempo = 200;

// change this to whichever pin you want to use
byte buzzer = 10;

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', 'a', 'b', 'c'},
  {'d', 'e', 'f', 'g'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void song(int melody[], int melody_size) {
  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes

  int notes = melody_size / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;
  
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    if (melody[thisNote] > 270) {digitalWrite(11, HIGH);}
    if (melody[thisNote] > 330) {digitalWrite(12, HIGH);}
    if (melody[thisNote] > 380) {digitalWrite(13, HIGH);}

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}

void loop() {
  // Play one song on loop 
  song(melody_odetojoy, sizeof(melody_odetojoy));
  delay(3000);

  /*
  char customKey = customKeypad.getKey(); // recevies signal from the key board 

  // Play piano on key board 
  if (customKey=='1'){tone(buzzer, NOTE_C6, 200);}
  else if (customKey=='1'){tone(buzzer, NOTE_C6, 200);}
  else if (customKey=='2'){tone(buzzer, NOTE_D6, 200);}
  else if (customKey=='3'){tone(buzzer, NOTE_E6, 200);}
  else if (customKey=='4'){tone(buzzer, NOTE_F6, 200);}
  else if (customKey=='5'){tone(buzzer, NOTE_G6, 200);}
  else if (customKey=='6'){tone(buzzer, NOTE_A6, 200);}
  else if (customKey=='7'){tone(buzzer, NOTE_B6, 200);}
  else if (customKey=='8'){tone(buzzer, NOTE_C7, 200);}
  else if (customKey=='9'){tone(buzzer, NOTE_D7, 200);}
  else if (customKey=='a'){tone(buzzer, NOTE_E7, 200);}
  else if (customKey=='b'){tone(buzzer, NOTE_F7, 200);}
  else if (customKey=='c'){tone(buzzer, NOTE_G7, 200);}
  else if (customKey=='d'){tone(buzzer, NOTE_A7, 200);}
  else if (customKey=='e'){tone(buzzer, NOTE_B7, 200);}
  else if (customKey=='f'){tone(buzzer, NOTE_C8, 200);}
  else if (customKey=='g'){tone(buzzer, NOTE_D8, 200);}
  */
}


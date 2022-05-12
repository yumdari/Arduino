#include "pitches.h"

#define melodyPin 4

int trig = 5;
int echo = 6;

unsigned long prevPlayTime = 0;
unsigned long playDuration = 0;
int currentMelody = 0;

//Mario main theme melody
int melodySize = 75;
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0, NOTE_G7, 0, 0,  0, NOTE_G6, 0, 0, 0, 
  NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, 
  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0,NOTE_C7, NOTE_D7, NOTE_B6, 0, 0,
  NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, 
  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0,NOTE_C7, NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 
  9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
  9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
};


void sing() {
    if(millis() < prevPlayTime + playDuration) {
        // music is playing. do nothing
        return;
    }
    // stop the tone playing:
    noTone(4);
    
    if(currentMelody >= melodySize)
        currentMelody = 0;
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/tempo[currentMelody];

    tone(melodyPin, melody[currentMelody], noteDuration);
    prevPlayTime = millis();
    playDuration = noteDuration * 1.30;
    
    currentMelody++;
}



void setup() {
  pinMode(melodyPin, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

}

void loop() {
  // Do what you want
//  digitalWrite(trig, HIGH); 
//  delayMicroseconds(10);
//  digitalWrite(trig, LOW);// 10ms만큼 출력
 
  unsigned long duration = pulseIn(echo, HIGH);
 
  // 초음파의 속도는 초당 340미터를 이동하거나, 29마이크로초 당 1센치를 이동합니다.
  // 따라서, 초음파의 이동 거리 = duration(왕복에 걸린시간) / 29 / 2 입니다.
  float distance = duration / 29.0 / 2.0;
  // play music
  sing();

  
}

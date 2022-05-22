#include "pitches.h"


const PROGMEM int shark_melody[] = {
  NOTE_D4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_FS4, NOTE_FS4, 0,
  NOTE_D4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_FS4, NOTE_FS4, 0,
  NOTE_D4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_FS4, NOTE_FS4, 0,
  NOTE_D4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_FS4, NOTE_FS4, 0,
  NOTE_D4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_FS4, NOTE_FS4, 0,

  NOTE_D4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_G4, 0, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_FS4, NOTE_FS4, 0,

  NOTE_C4, NOTE_D4, NOTE_F4, 0, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_C4, NOTE_D4, NOTE_F4, 0, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_C4, NOTE_D4, NOTE_F4, 0, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, 0,
  NOTE_C4, NOTE_D4, NOTE_F4, 0, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_C4, NOTE_D4, NOTE_F4, 0, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_C4, NOTE_D4, NOTE_F4, 0, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, 0,

  NOTE_C4, NOTE_D4, NOTE_F4, 0, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_C4, NOTE_D4, NOTE_F4, 0, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_C4, NOTE_D4, NOTE_F4, 0, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_F4, 0
};


const PROGMEM int shark_noteDurations[] = {
  4, 4, 8, 8, 16, 16, 16, 8, 8, 8, 8, 8, 8, 16, 16, 16, 8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8,8, 4,
  4, 4, 8, 8, 16, 16, 16, 8, 8, 8, 8, 8, 8, 16, 16, 16, 8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8,8, 4,
  4, 4, 8, 8, 16, 16, 16, 8, 8, 8, 8, 8, 8, 16, 16, 16, 8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8,8, 4,
  4, 4, 8, 8, 16, 16, 16, 8, 8, 8, 8, 8, 8, 16, 16, 16, 8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8,8, 4,
  4, 4, 8, 8, 16, 16, 16, 8, 8, 8, 8, 8, 8, 16, 16, 16, 8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8,8, 4,

  4, 4, 4, 8, 16, 16, 16, 8, 8, 8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8, 8, 16, 16, 16, 8, 8, 8, 8, 8, 4,

  4, 4, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 4, 4,
  4, 4, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 4, 4,

  4, 4, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8, 8, 16, 16, 16, 8, 8, 8, 4, 4


};

const PROGMEM int cannon_melody[] = {NOTE_A6, NOTE_FS6, NOTE_G6, NOTE_A6, NOTE_FS6, NOTE_G6, NOTE_A6, NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_D6, NOTE_E6, NOTE_FS6, NOTE_G6, NOTE_FS6, NOTE_D6, NOTE_E6, NOTE_FS6, NOTE_FS5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_FS5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_FS5, NOTE_E5, NOTE_FS5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_FS5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_G5, NOTE_B5, NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_D6, NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_D6, NOTE_E6, NOTE_FS6, NOTE_G6, NOTE_A6};

const PROGMEM int cannon_noteDurations[] = {8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 16, 16, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};

const PROGMEM int birthday_melody[] = {
NOTE_G6, NOTE_G6, NOTE_A6, NOTE_G6, NOTE_C5, NOTE_B6,
NOTE_G6, NOTE_G6, NOTE_A6, NOTE_G6, NOTE_D5, NOTE_C5,
NOTE_G6, NOTE_G6, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_B6, NOTE_A6,
NOTE_F5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_C5
};

const PROGMEM int birthday_noteDurations[] = {
8, 8, 4, 4, 4, 2,
8, 8, 4, 4, 4, 2,
8, 8, 4, 4, 4, 4, 4,
8, 8, 4, 4, 4, 2
};

const PROGMEM int bear_melody[] = {
NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,               
NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,               
NOTE_G5,NOTE_G5,NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,       
NOTE_C5,NOTE_C5,NOTE_C5,                               
NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,                       
NOTE_G5,NOTE_G5,NOTE_G5,                               
NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,                       
NOTE_G5,NOTE_G5,NOTE_G5,                               
NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,                       
NOTE_G5,NOTE_G5,NOTE_G5,NOTE_A5,NOTE_G5,               
NOTE_C6,NOTE_G5,NOTE_C6,NOTE_G5,                       
NOTE_E5,NOTE_D5,NOTE_C5                                
};

const PROGMEM int bear_noteDurations[]={ 4,8,8,4,4, 4,8,8,4,4, 8,8,4,8,8,4, 4,4,2, 4,4,4,4, 4,4,2, 4,4,4,4, 4,4,2, 4,4,4,4, 8,8,8,8,2, 4,4,4,4, 4,4,2 };

void setup() {

  Serial.begin(9600);
  pinMode(12, INPUT);

  Serial.println(sizeof(shark_melody)/sizeof(int));

}

int song = 0;
bool start = false;
int button = 0;
int buttonPrev = 0;
int skipButton = 0;
int skipButtonPrev = 0;

void loop() {

  //Serial.println(digitalRead(12));

  button = digitalRead(12);

  if( button == 0 && buttonPrev == 1 )
  {
    song++;
    if(song > 4)
    {
      song = 1;
    }
    start = true;
  }

  if(start)
  {
    if( song == 1)
    {
      for (int i = 0; i < sizeof(shark_melody)/sizeof(int); i++) 
      {      
        int melody = pgm_read_word_near(shark_melody + i);
        int noteDuration = 1500 / pgm_read_word(shark_noteDurations + i);

        tone(2, melody, noteDuration);  
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);     
        noTone(2);

        skipButton = digitalRead(12);

        if(skipButton == 0 && skipButtonPrev == 1)
        {
          break;
        }
        skipButtonPrev = skipButton;
      }
    }
    else if( song == 2)
    {
      //for(int repeat = 0; repeat < 3; repeat++)
      {
        for(int i = 0; i < sizeof(cannon_melody)/sizeof(int); i++) 
        {      
          int melody = pgm_read_word_near(cannon_melody + i);
          int noteDuration = 1500 / pgm_read_word(cannon_noteDurations + i);

          tone(2, melody, noteDuration);  
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);     
          noTone(2);

          skipButton = digitalRead(12);

          if(skipButton == 0 && skipButtonPrev == 1)
          {
            break;
          }
          skipButtonPrev = skipButton;
        }
      }
    }
    else if( song == 3)
    {
      for(int i = 0; i < sizeof(birthday_melody)/sizeof(int); i++) 
      {      
        int melody = pgm_read_word_near(birthday_melody + i);
        int noteDuration = 1500 / pgm_read_word(birthday_noteDurations + i);

        tone(2, melody, noteDuration);  
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);     
        noTone(2);

        skipButton = digitalRead(12);

        if(skipButton == 0 && skipButtonPrev == 1)
        {
          break;
        }
        skipButtonPrev = skipButton;
      }
    }
    else if( song == 4)
    {
      for(int i = 0; i < sizeof(bear_melody)/sizeof(int); i++) 
      {      
        int melody = pgm_read_word_near(bear_melody + i);
        int noteDuration = 1500 / pgm_read_word(bear_noteDurations + i);

        tone(2, melody, noteDuration);  
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);     
        noTone(2);

        skipButton = digitalRead(12);

        if(skipButton == 0 && skipButtonPrev == 1)
        {
          break;
        }
        skipButtonPrev = skipButton;
      }
    }

    start = false;
  }

  buttonPrev = button;


}

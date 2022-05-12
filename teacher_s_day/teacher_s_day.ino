#include "SimplePitches.h"

int melody[] = {
D4, B4, B4,
C5, B4, A4, G4, E4,
D4, G4, FS4, G4,
A4, 0,

D4, B4, B4,
C5, B4, A4, G4, E4,
FS4, G4, A4, B4,
G4, 0,

G4, FS4, E4, E4,
E4, G4, C5, E5, D5,
C5, E4, E4, FS4, G4,
A4, 0,

D4, D5, B4,
A4, C5, B4, A4, G4,
E4, D4, FS4, A4,
G4, 0,

B4, C5, D5,
B4, C5, D5, G4,
A4, D4, C5, B4,
A4, 0,

B4, D5,
B4, B4, B4, E5,
D5, C5, B4, A4, D4, A4, B4,
G4, 0
};


int noteDurations[] = {
4,4,4,
6,6,6,6,4,
4,4,6,6,
2,4,

6,3,6,
6,6,6,6,4,
6,6,4,4,
2,4,

10,12,3,6,
6,6,10,12,4,
10,12,4,6,6,
2,4,

6,6,3,6,
6,6,10,12,4,
3,6,6,6,
2,4,

10,12,2,
12,12,12,2,
3,8,8,8,
2,4,

4,2,
8,8,8,2,
8,8,8,10,12,10,12,
2,4
};


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
for (int thisNote = 0; thisNote < 288; thisNote++) 
{

int noteDuration = 750 / noteDurations[thisNote];
tone(2, melody[thisNote], noteDuration);

int pauseBetweenNotes = noteDuration * 2.50;
delay(pauseBetweenNotes);

noTone(2);}
}

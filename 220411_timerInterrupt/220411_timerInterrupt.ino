#include <MsTimer2.h>

void setup() {
  MsTimer2::set(1000, isr);
  MsTimer2::start();
  pinMode(13, OUTPUT);  
}

void isr(){
  static boolean state = HIGH;
  digitalWrite(13, state);
  state = !state;
}

void loop() {
 
}

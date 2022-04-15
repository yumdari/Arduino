#include <SimpleTimer.h>

int ledState;
int LED = 26;
SimpleTimer timer;

void timer1(){
  ledState=!ledState;
  
}

void setup() {
  timer.setInterval(1000,timer1);
}

void loop() {

  timer.run(timer1);
  digitalWrite(LED, ledState);
}

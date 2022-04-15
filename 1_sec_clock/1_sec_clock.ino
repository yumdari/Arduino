#include <SimpleTimer.h>

#define LED 26

int i = 0;
int t = 0;
int s = 0;
int m = 0;
int h = 0;


unsigned long Count = 0;
unsigned long Clock = 0;

SimpleTimer timer;

void setup() {

  timer.setInterval(1000, Count);

  pinMode(Clock, OUTPUT);

  pinMode(LED, OUTPUT);

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(2),Count,RISING); //count clock

  i = millis();
}

void loop() {
  Clock_Pulse;

}

void Clock_Pulse() {
  if (digitalRead(26)) {
    digitalWrite(Clock, HIGH);
    Serial.println(1);
  }
  else {
    digitalWrite(Clock, LOW);
    Serial.println(0);
  }
}

void Sec_Clock() {
  if (i == 1000) {
    s = i / 1000;
    if (m > 60) {
      m = i / 60;
      h = m / 60;
    }
    else if (i < 60) {
      s = i;
    }
  }
  Serial.print(h );
  Serial.print(m );
  Serial.print(s );
}

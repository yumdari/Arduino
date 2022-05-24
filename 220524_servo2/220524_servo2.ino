#include <ESP32_Servo.h>

static const int servoPin = 27;

Servo servo1;

int pos = 0;

unsigned long curTimeMs = 0;

void setup() {
    Serial.begin(115200);
    servo1.attach(servoPin);
    curTimeMs = millis();
}
  
void loop() {
if(curTimeMs + 10 < millis()){
        servo1.write(pos);
        if(pos<180){
        pos++;
        }
       curTimeMs = millis();
    }
  }

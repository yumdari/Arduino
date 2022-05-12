#include<SoftwareSerial.h>

#define TX 6
#define RX 7

SoftwareSerial soft_Serial(TX,RX);

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  soft_Serial.begin(115200);
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  soft_Serial.write("s");
  digitalWrite(13, HIGH);
  delay(1000);
  soft_Serial.write('w'); 
  digitalWrite(13, LOW);
  delay(1000);

//  String myString = soft_Serial.readString();
}

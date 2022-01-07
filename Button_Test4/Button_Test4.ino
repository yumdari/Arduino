int pinSwitch = 34;
int pinLed = 26;
int ledStatus = LOW;
int flag = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pinSwitch, INPUT);
  pinMode(pinLed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(pinSwitch)) {
    if (ledStatus == 0) {
      ledStatus = 1;
      Serial.println(ledStatus);
      digitalWrite(pinLed, ledStatus);
    }
    else if (ledStatus == 1) {
      ledStatus = 0;
      Serial.println(ledStatus);
      digitalWrite(pinLed, ledStatus);
    }
  }
  else {
    Serial.println(ledStatus);
    digitalWrite(pinLed, ledStatus);
  }
}

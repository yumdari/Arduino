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
    if (flag == 0) {
      ledStatus = (ledStatus == LOW) ? HIGH : LOW;
      digitalWrite(pinLed, ledStatus);
      Serial.println(ledStatus);
      ledStatus = !ledStatus;
      flag = 1;
      delay(1);
    }
    else if (flag == 1) {
      Serial.println(ledStatus);
      delay(1);
    }
  }
  else {
    flag = 0;
    Serial.println(ledStatus);
    delay(1);
  }
}

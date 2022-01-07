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
      delay(20);
      ledStatus = (ledStatus == LOW) ? HIGH : LOW;
      digitalWrite(pinLed, ledStatus);
      Serial.println("pushed");
      delay(500);
      flag = 1;
      delay(20);
    }
    else if (flag == 1) {
      Serial.println("pulled");
      delay(500);
    }
  }
  else {
    flag = 0;
    Serial.println("pulled");
    delay(500);
  }
}

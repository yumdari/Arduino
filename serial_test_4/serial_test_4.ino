int led = 26;


void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  Serial.setTimeout(100);

  Serial.println("LED Control");
}

void loop() {
}

void serialEvent() {
  if (Serial.available() > 0) {
    String ledOnOff = Serial.readStringUntil('\n');

    if (ledOnOff == "on") {
      digitalWrite(led, HIGH);
      Serial.println("LED On");
    }
    else if (ledOnOff == "off") {
      digitalWrite(led, LOW);
      Serial.println("LED Off");
    }
  }
}

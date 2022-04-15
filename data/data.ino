int LED = 26;
void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);
  digitalWrite(LED, LOW);
}

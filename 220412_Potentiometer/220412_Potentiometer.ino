#define LED 10

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  int analogIn = analogRead(A0);
  int analogOut = (analogIn, 0, 1023, 0, 255);
  Serial.println(analogOut);
  analogWrite(LED, analogOut);
}

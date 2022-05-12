#define CDS A3
#define LED 10

void setup() {
  pinMode(CDS, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  int analogIn = analogRead(A3);
  int analogOut = map(analogIn, 0, 1023, 0, 255);
  analogWrite(LED, analogOut);

}

void setup() {
    Serial.begin(9600);
  // put your setup code here, to run once:
  DDRA = B11111111;
  DDRC = B11111111;
  //A4,A5,A6,A7,C7,C6,C5,C4
}

void loop() {
  PORTA = B00000001;
  PORTC = B00000001;
  delay(1000);
  PORTA = B00000000;
  PORTC = B00000000;
  delay(1000);
  PORTA << 1;
  PORTC << 1;
  
  // put your main code here, to run repeatedly:

}

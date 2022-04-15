int buzzer = 9;
void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(buzzer,1);
  delay(1000);
  analogWrite(buzzer,0);
  delay(1000);
}

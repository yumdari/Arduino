int LED=26;
int SW=34;
void setup() {
  // put your setup code here, to run once:
  pinMode(SW,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(SW)==HIGH)
  digitalWrite(LED,HIGH);
  else
  digitalWrite(LED,LOW);
}

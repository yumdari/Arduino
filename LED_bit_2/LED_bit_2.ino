int i=0;
int j=0;

unsigned long preTime = 0;
unsigned long nowTime = 0;
unsigned char ledState = 0;

void setup() {
  DDRA = 0xFF;
  DDRC = 0xFF;
  //A4,A5,A6,A7,C7,C6,C5,C4
}

void loop() {
  nowTime = millis();
  if(nowTime - preTime >= 50)
  preTime = nowTime;
  for(i=0;i<5;i++)
  {
  PORTA = 0x10 << i;
  delay(50);
  }
  for(i=0;i<5;i++)
  {
  PORTC = 0x80 >> i;
  delay(50);
  }
}

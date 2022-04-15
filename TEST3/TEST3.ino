 #include <MsTimer2.h>

 int i=0;
 int buzz=22;
 int buzzState=0;
 unsigned long preTime = 0;
 unsigned long curTime = 0;
 unsigned char ledState = 0;
 int SW1=34;
 int SW2=34;
 int t=50;

 void setup() {
  DDRA = 0xFF;
  DDRC = 0xFF;
  //A4,A5,A6,A7,C7,C6,C5,C4
  pinMode(buzz, OUTPUT);
  MsTimer2::set(1000, timerISR);
  MsTimer2::start();
  pinMode(SW1,INPUT_PULLUP);
  pinMode(SW2,INPUT_PULLUP);
 }

 void loop() {
  curTime = millis();
  if(curTime - preTime >= 500)
  {
    preTime = curTime;
    for(i=0;i<5;i++)
    {
    PORTA = 0x10 << i;
    delay(t);
    }
  for(i=0;i<5;i++)
    {
    PORTC = 0x80 >> i;
    delay(t);
    }
  if(digitalRead(SW1)==LOW)
    t+=50;
  if(digitalRead(SW2)==LOW)
    t-=50;
  }
}

 void timerISR() {
  if(buzzState == 0) 
    buzzState = 1;
  else 
    buzzState = 0;
  digitalWrite(buzz, buzzState);
 }

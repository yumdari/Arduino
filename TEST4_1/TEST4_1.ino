 #include <MsTimer2.h>

 int i=0;
 int buzz=9;
 int buzzState=0;
 int SW1=34;
 int SW2=35;
 int t=50;

 void setup() {
  DDRA = 0xFF;
  DDRC = 0xFF;
  //A4,A5,A6,A7,C7,C6,C5,C4
  pinMode(buzz, OUTPUT);
  MsTimer2::set(5000, timerISR);
  MsTimer2::start();
  pinMode(SW1,INPUT_PULLUP);
  pinMode(SW2,INPUT_PULLUP);
}

 void loop() {
 
    if(digitalRead(SW1)==HIGH)
     t+=20;
    if(digitalRead(SW2)==HIGH)
     t-=10;
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
    }   // toggle LED pin

}

 void timerISR() {
  if(buzzState == 0) 
    buzzState = 1;
  else 
    buzzState = 0;
  digitalWrite(buzz, buzzState);
 }

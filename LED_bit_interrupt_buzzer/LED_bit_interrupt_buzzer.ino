int i=0;
int SW1=34;//Start&Stop button
int SW2=35;//Key button
int LEDstate=0;
int buzzer=9;

unsigned long preTime = 0;
unsigned long nowTime = 0;
unsigned char buzzstate = 0;

void setup() {
  pinMode(SW,INPUT_PULLUP);
  DDRA = 0xFF;
  DDRC = 0xFF;
  //A4,A5,A6,A7,C7,C6,C5,C4
  attachInterrupt(0,SS,FALLING);
  attachInterrupt(1,key,FALLING);
  pinMode(buzzer, OUTPUT);
  nowTime = millis();
}
void SS() {
  LEDstate=!LEDstate;
  //if Start&Stop button pulled down, change LED's state.
}

void Key() {
  if(t>5)
  t=0;
  else
  t++;
  //when Key button pulled, 't' will be increasing.
}

void loop() {
  if(LEDstate==1)
  {
    for(i=0;i<5;i++)
      {
        PORTA = 0x10 << i;
        delay(t*50);
      }
    for(i=0;i<5;i++)
      {
        PORTC = 0x80 >> i;
        delay(t*50);
      }
   }
   else if(LEDstate==0)
   PORTA = 0x00;
   PORTC = 0x00;
   //LED blink
 
   if(nowTime - preTime >= 1000)
   {
      preTime = nowTime;
      buzzstate=!buzzstate;
      digitalWrite(buzzer,buzzstate);
   }    
   //buzzer will buzz every 1000 ms.
}

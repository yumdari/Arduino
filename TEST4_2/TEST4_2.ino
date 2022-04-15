 #include <MsTimer2.h>

 int i=0;
 int buzz=9;
 int buzzState=1;
 int SW1=34;
 int SW2=35;
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
    key_input();
    led_shift();
}

 void key_input(){
    if(t<10)
      t=10;
    else if(t>90)
      t=90;
    if(digitalRead(SW1)==HIGH)
     t+=20;
    if(digitalRead(SW2)==HIGH)
     t-=10;
 }

void led_shift(){
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
  buzzState=!buzzState;
  analogWrite(buzz,buzzState);
  
 }

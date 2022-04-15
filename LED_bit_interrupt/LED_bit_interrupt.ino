int i=0;
int SW=34;
int state=0;

void setup() {
  pinMode(SW,INPUT_PULLUP);
  DDRA = 0xFF;
  DDRC = 0xFF;
  //A4,A5,A6,A7,C7,C6,C5,C4
  attachInterrupt(0,SS,FALLING);
  attachInterrupt(1,key,FALLING);
}
void SS() {
  state=!state;
}

void Key() {
  if(t>5)
  t=0;
  else
  t++;
}

void loop() {
  if(digitalRead(Key)==LOW)
  {t++;}
  else if(t>5)
  {t=0;}
  if(state==1)
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
   else if(state==0)
   PORTA = 0x00;
   PORTC = 0x00;
}

#define buzz 9
int i=0;


void setup()

{
  pinMode(buzz, OUTPUT);
  DDRA = 0xFF;
  DDRC = 0xFF;
  //A4,A5,A6,A7,C7,C6,C5,C4
  // initialize timer1 

  noInterrupts();           // disable all interrupts

  TCCR1A = 0;

  TCCR1B = 0;

  TCNT1  = 0;


  OCR1A = 31250;            // compare match register 16MHz/256/2Hz

  TCCR1B |= (1 << WGM12);   // CTC mode

  TCCR1B |= (1 << CS12);    // 256 prescaler 

  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt

  interrupts();             // enable all interrupts

}


ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine

{

  analogWrite(buzz, analogRead(buzz) ^ 1);   // toggle LED pin

}


void loop()

{
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

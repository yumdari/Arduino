long time = millis() ;
int i = 0;
int j = 0;
int t = 50; // interval
void setup()
{
  DDRA = 0xF0;
  DDRC = 0xF0;
}

void loop()
{
  if (time + t < millis())
  {
    PORTA = 0x10 << i;
    i++;
    time = millis() ;
    if (i > 4) {
      PORTA = 0x00;
      PORTC = 0x80 >> j;
      j++;
      time = millis() ;
      if ( j > 4)
      {
        i = 0;
        j = 0;
      }
    }
  }
}

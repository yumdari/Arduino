long time = millis() ;
int i = 0;
int j = 0;
int t = 100; // interval
void setup()
{
  DDRA = 0xF0;
  DDRC = 0xF0;
}

void loop()
{
  if (time + t < millis())
  {
    for (i = 0; i < 5; i++)
    {
      PORTA = 0x10 << i;
    }
      PORTA = 0x00;
  }
}

#include <MsTimer2.h>

int i = 0;
int buzz = 9; // set buzzer up to D9
int buzzState = 1;
int SW1 = 34; // speed down
int SW2 = 35; // speed up
int SW3 = 36; // LED start&stop
int SW4 = 37; // LED reset
int t = 50; // initial delay

unsigned int curTime = 0;
unsigned int preTime = 0;
unsigned char ledState = 0;

void setup() {
  DDRA = 0xFF;
  DDRC = 0xFF;
  //A4,A5,A6,A7,C7,C6,C5,C4
  pinMode(buzz, OUTPUT);
  MsTimer2::set(1000, timer);
  MsTimer2::start();
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), LED_reset, FALLING);
}

void loop() {
  key_input();
  led_shift();
  LED_State();
}

void key_input() {
  if (t < 10)
    t = 10;
  else if (t > 90)
    t = 90;
  if (digitalRead(SW1) == HIGH)
    t += 10;
  if (digitalRead(SW2) == HIGH)
    t -= 10;
}

void led_shift() {
  curTime = millis();
  if (curTime - preTime > t)
  {
    for (i = 0; i < 5; i++)
    {
      PORTA = 0x10 << i;
      delay(t);
    }
    for (i = 0; i < 5; i++)
    {
      PORTC = 0x80 >> i;
      delay(t);
    }   // toggle LED pin
    curTime = preTime;
  }
}

void LED_State() {
  if (digitalRead(SW3) == HIGH)
  {
    PORTA = 0x00;
    PORTC = 0x00;
  }
}

void LED_reset() {
}


void timer() {
  buzzState = !buzzState;
  analogWrite(buzz, buzzState); // periodly buzz
}
void timer_stop() {
  MsTimer2::stop(); // if SW4 pulled, timer will be stop
}

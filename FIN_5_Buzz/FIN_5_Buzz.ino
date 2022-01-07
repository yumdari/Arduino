#include <MsTimer2.h>

unsigned long curTimeMs = 0;
int i = 0;
int j = 0;
int t = 50; // initial interval
int buzz = 6; // set buzzer up to D9
int ledState = 1; //initial LED state
int SW1 = 34; // speed down
int SW2 = 35; // speed up
int SW3 = 36; // LED reset
int SW5 = 38; // LED start&stop

int hour = 0, minute = 0, second = 0;

unsigned long count = 0;
int clockSignal = 5; //clock check

int numTones = 30;
int tones[] = {330, 294, 261, 294, 330, 330, 330, 0,294, 294, 294,0,330, 392, 392,0, 330, 294, 261, 294, 330, 330, 330,0,294, 294, 330, 294, 261, 523};

void setup()
{
  MsTimer2::set(1000, clocks);
  MsTimer2::start();

  DDRA = 0xF0;  // LED 1,2,3,4
  DDRC = 0xF0;  // LED 8,7,6,5
  pinMode(buzz, OUTPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW5, INPUT);
  pinMode(clockSignal, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), Count_Clock, RISING);
  Serial.begin(9600);
  curTimeMs = millis();
}

void loop() {
  Buzz_Timer();
  Led_Shift();
  Led_Reset();
}

void Led_Shift()
{
  if (curTimeMs + t < millis())
  {
    Led_State();
    Key_Input();
    PORTA = 0x10 << i;
    Clock_Signal();
    Led_State();
    i++;
    curTimeMs = millis() ;
    if (i > 4) {
      PORTA = 0x00;
      Key_Input();
      PORTC = 0x80 >> j;
      Clock_Signal();
      Led_State();
      j++;
      curTimeMs = millis() ;
      if ( j > 4)
      {
        i = 0;
        j = 0;
      }
    }
  }
}

void Key_Input() {
  if (digitalRead(SW1) == HIGH)
    t += 5;
  if (digitalRead(SW2) == HIGH)
    t -= 5;
  if (t < 10)
    t = 10;
  else if (t > 100)
    t = 100;
}

void Led_Reset() {
  if (digitalRead(SW3) == HIGH)
  {
    for (i = 1; i < 4; i++)
    {
      PORTA = 0xF0;
      PORTC = 0xF0;
      delay(100);
      PORTA = 0x00;
      PORTC = 0x00;
      delay(100);
    }
    t = 50;
  }
}
//blink LEDs x3 and set interval up 50 ms

void Led_State() {
  if (digitalRead(SW5) == HIGH) {
    ledState = !ledState;
  }
  if (ledState == 0) {
    PORTA = 0x00;
    PORTC = 0x00;
  }
}

void Buzz_Timer() {
  if (second % 10 == 0) {
    for (int i = 0; i < numTones; i++) {
      //numTones(8)의 수만큼 반복 실행합니다.
      // tone함수를 통해 피에조부저에서 소리가 나며 tones[]배열에 있는 주파수에 해당하는 음계가 출력됩니다.
      tone(buzz, tones[i]);
    Buzz_Stop();
  }
}

void Buzz_Stop() {
  if //(second != 0) 
       (second%2=0) {
    noTone(buzz);
  }
}

void clocks() {
  second++;
  if (second == 60)
  {
    second = 0;
    minute++;
  }
  if (minute == 60)
  {
    minute = 0;
    hour++;
  }
  Serial.print(hour);
  Serial.print(" : ");
  Serial.print(minute);
  Serial.print(" : ");
  Serial.print(second);
  Serial.print(" ::: ");
  Serial.println(count);
}// 1 sec clock

void Clock_Signal() {
  if (PORTA == 0x10 || PORTA == 0x40 || PORTC == 0x80 || PORTC == 0x20) {
    digitalWrite(clockSignal, HIGH);
  }
  else {
    digitalWrite(clockSignal, LOW);
  }
}

void Count_Clock() {
  count++;
}

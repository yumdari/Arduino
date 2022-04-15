include<stdio.h>
  int LED1=26;
  int LED2=27;
  int LED3=28;
  int LED4=29;
  int LED5=30;
  int LED6=31;
  int LED7=32;
  int LED8=33;
  int SW1=34;


void setup()
{

  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(LED6,OUTPUT);
  pinMode(LED7,OUTPUT);
  pinMode(LED8,OUTPUT);
  pinMode(SW1,INPUT_PULLUP);
}
void loop()
{
    digitalWrite(LED1,HIGH);
    delay(50);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,HIGH);
    delay(50);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,HIGH);
    delay(50);
    digitalWrite(LED3,LOW);
    digitalWrite(LED4,HIGH);
    delay(50);
    digitalWrite(LED4,LOW);
    digitalWrite(LED5,HIGH);
    delay(50);
    digitalWrite(LED5,LOW);
    digitalWrite(LED6,HIGH);
    delay(50);
    digitalWrite(LED6,LOW);
    digitalWrite(LED7,HIGH);
    delay(50);
    digitalWrite(LED7,LOW);
    digitalWrite(LED8,HIGH);
    delay(50);
    digitalWrite(LED8,LOW);

    digitalWrite(LED7,HIGH);
    delay(50);
    digitalWrite(LED7,LOW);
    digitalWrite(LED6,HIGH);
    delay(50);
    digitalWrite(LED6,LOW);
    digitalWrite(LED5,HIGH);
    delay(50);
    digitalWrite(LED5,LOW);
    digitalWrite(LED4,HIGH);
    delay(50);
    digitalWrite(LED4,LOW);
    digitalWrite(LED3,HIGH);
    delay(50);
    digitalWrite(LED3,LOW);
    digitalWrite(LED2,HIGH);
    delay(50);
    digitalWrite(LED2,LOW);

   
}

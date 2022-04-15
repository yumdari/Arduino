#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Servo.h>

#define CDS A3
#define LED 10

int ledState = 0;
int cdsKey = 0;

Servo myservo;

LiquidCrystal_I2C lcd(0x27, 16, 2); // set LCD address to 0x27 for a 16 chars and 2 line display
//address : 0x3F, 0x27 
void setup() {
  lcd.init(); //LCD initiallize
  lcd.backlight(); // brightend the LCD backlight
  lcd.setCursor(0, 0); // move cursor
  pinMode(CDS, INPUT);

  myservo.attach(9);
  pinMode(A0, INPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
//  int analogIn = analogRead(A0);
//  int val = map(analogIn, 0, 1023, 0, 180);
//  myservo.write(val);
  int val = analogRead(A3);
  cdsKey = val;
  
  if(val<=200){
    ledState = 1;
  }
  else {
    ledState = 0;
  }
  
  lcd.setCursor(0,0);
  lcd.print("test");
  lcd.setCursor(0, 1); // move cursor
  lcd.print("CDS:"); // lcd print

  if(val<100){
    lcd.setCursor(6, 1);
    lcd.print(" ");
  }
  lcd.setCursor(4, 1);
  lcd.print(val);

  digitalWrite(LED, ledState);
//  delay(10);

  lcd.setCursor(8, 1);

  if(ledState == 1){
    lcd.print("ON ");
  }
  else{
    lcd.print("OFF");
  }

  Serial.println(val);

  

//  if(Serial.available()){
//    lcd.setCursor(7,0);
//    lcd.print(Serial.read());
//  }



//  if(Serial.available())
//  {
//    lcd.clear();
////    delay(100);
//    lcd.setCursor(6,0);
//
//    while(Serial.available()>0){
//      if(Serial.read() != 10){
//      lcd.write(Serial.read());
//      }
//    }
//  }

 
}

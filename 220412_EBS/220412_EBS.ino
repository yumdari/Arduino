#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <SPI.h>

#include <Stepper.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc(SS_PIN, RST_PIN);

const int stepsPerRevolution = 2048;
// 2048 : 한 바퀴(360도), 1024 : 반바퀴 (180도)

Stepper myStepper(stepsPerRevolution, 11, 9, 10, 8);

void setup() {

  SPI.begin();
  mfrc.PCD_Init();
  
  pinMode(A0,INPUT);
  Serial.begin(9600);
}

void motorControl(){
//  int analogIn = analogRead(A0);
//  int motorSpeed = map(analogIn, 0, 1023,0, 100);
  
  myStepper.setSpeed(16);
  
//  myStepper.step(stepsPerRevolution); // 시계 반대 방향으로 한 바퀴 회전
//  delay(500);

//  myStepper.step(stepsPerRevolution); // 시계 방향으로 한 바퀴 회전
//  delay(500);
    myStepper.step(45);
}

void loop() {

   if(!mfrc.PICC_IsNewCardPresent()){
    return; //Exception
  }
  if(!mfrc.PICC_ReadCardSerial()){
    return; //Exception
  }

  if((mfrc.uid.uidByte[0] == 195) &&
     (mfrc.uid.uidByte[1] == 151) &&
     (mfrc.uid.uidByte[2] == 29) &&
     (mfrc.uid.uidByte[3] == 12)){
      Serial.println("Autorized access");
      motorControl();
     }
  else{
      Serial.println("Access denied");
  }
  
  Serial.print("Card UID:");
  for(byte i = 0; i < 4; i++){
    Serial.print(mfrc.uid.uidByte[i]);
    Serial.print(" ");
  }
  Serial.println();

  
  
  
}

#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include <SPI.h>


#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc(SS_PIN, RST_PIN);

/// Radio Frequency Identification
//Tag and Reader

void setup() {

  Serial.begin(9600);
  SPI.begin();
  mfrc.PCD_Init();

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
      delay(500);
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

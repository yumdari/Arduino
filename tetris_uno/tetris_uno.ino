#include <SoftwareSerial.h>
#define LED 13

SoftwareSerial ble(2, 3);
String myStr = "";


void setup() {
  Serial.begin(115200); // ble 값이 뭐가 뜨는지 확인용
  //ble.begin("ESP32Tetris"); //AT+BAUD8 : 115200 보드레이트 값
  ble.begin(115200);
  pinMode(LED, OUTPUT);
}

void loop() {
    while(ble.available()){ // 블루투스 수신이 있다면
//    char myChar = (char)ble.read();
//    myStr += myChar;
//    delay(5);
//    Serial.println(myChar);
    Serial.write(ble.read()); // 시리얼 모니터에 블루투스 수신 값 출력
  }
//  if(!myStr.equals(""))
//  {
//    if(myStr =="ledon\r\n"){
//      digitalWrite(LED, HIGH);
//    }
//    else if (myStr =="ledoff\r\n"){
//      digitalWrite(LED, LOW);
//    }
//    myStr="";
//  }
  if(Serial.available()){ // 시리얼 수신이 있다면
    ble.write(Serial.read()); // 블루투스 기기에 시리얼 수신 값 출력
  }
}

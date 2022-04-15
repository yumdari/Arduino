#include <IRremote.hpp>

#define RECV_PINT = 2;

#define IR0 0XFF6897
#define IR1 0XFF30CF
#define IR2 0XFF18E7
#define IR3 0XFF7A85
#define IR4 0XFF10EF
#define IR5 0XFF38C7
#define IR6 0XFF5AA5
#define IR7 0XFF42BD
#define IR8 0XFF4AB5
#define IR9 0XFF52AD

#define LED 13

IRrecv ir(2);
decode_results results;

int irFlag = 0; 

void setup() {
  Serial.begin(9600);
  ir.enableIRIn();
  pinMode(LED, OUTPUT);
//  int numArray;
}

void loop() {
  
  if(ir.decode(&results)){ // 리모콘 작동 신호 감지 시 ir.decode(&results) = 1
    if(irFlag == 0){
    Serial.println(results.value, HEX);
    
    irFlag = 1; 
    ir.resume();
    }
  }

//  if(results.value == 0XFF30CF){
//    digitalWrite(LED, HIGH);
//  }
//  else if(results.value == 0XFF18E7) {
//    digitalWrite(LED, LOW);
//  }
 
//  delay(100);
//  if(results.value == numArray[idx]){
//    Serial.println(numArray[idx]);
//  }
//  else{
//    Serial.println("값 없음");
//  }
}

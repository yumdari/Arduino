#define PIRINPUT 7
int pirVal = 0; // PIR 센서 신호 판별 변수

void setup() {
  DDRB = B00111000; // 11, 12, 13 번 핀을 출력핀으로 설정
  Serial.begin(9600);
  
  pinMode(PIRINPUT, INPUT);
}

void loop() {
 pirVal = digitalRead(PIRINPUT);

  if (pirVal == HIGH){
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    Serial.println("동작 감지");
  }
  else {
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
//    Serial.println("동작 미감지");
  }
  
  
//  PORTB = B00100000; // 13, Red LED
//  delay(1000);
//  PORTB = B00010000; // 12, Green LED
//  delay(1000);
//  PORTB = B00001000; // 11, Blue LED
//  delay(1000);
  
}

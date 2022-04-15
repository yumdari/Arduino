///HC-06 : 클래식 블루투스, BLE 이전 제품
///아이폰은 블루투스 4.0 버전 이후인 BLE 이후부터 지원
///HM-10 같은 BLE 모듈 사용하여야함 
void setup() {
  Serial1.begin(9600);
}

void loop() {
  Serial1.println("hello");
  delay(1000);
}

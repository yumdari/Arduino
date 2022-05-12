
/*
 제목    : 초음파센서로 거리 측정하기
 내용   : 초음파센서로부터 10cm 이내로 물체가 감지되었을때 BUZZER가 켜지도록 만들어 봅시다.
 */
 
// 초음파센서의 송신부를 8번핀으로 선언하고 수신부는 9번핀으로 선언합니다.
int trig = 5;
int echo = 6;


 
// BUZZER를 A0핀으로 설정합니다.
int piezo = 4;

int numTones = 38;
//int tones[] = {261, 294, 330, 349, 392, 440, 494, 523}; numTones = 8
int tones[] = {293, 391, 493, 587, 587, 523, 493, 440, 493, 391, 493, 587, 783, 783, 783, 880, 693, 659, 698, 440, 554, 698, 880, 783, 698, 659, 698, 783, 698, 659, 587, 523, 493, 523, 587, 523, 391, 440};

 
// 실행시 가장 먼저 호출되는 함수이며, 최초 1회만 실행됩니다.
// 변수를 선언하거나 초기화를 위한 코드를 포함합니다.
void setup() {
  // 초음파센서의 동작 상태를 확인하기 위하여 시리얼 통신을 설정합니다. (전송속도 9600bps)
  Serial.begin(9600);
  //초음파 송신부-> OUTPUT, 초음파 수신부 -> INPUT,  BUZZER핀 -> OUTPUT
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(piezo, OUTPUT);
}
 
// setup() 함수가 호출된 이후, loop() 함수가 호출되며,
// 블록 안의 코드를 무한히 반복 실행됩니다.
void loop() {
//  digitalWrite(trig, LOW);
//  digitalWrite(echo, LOW);
//  delayMicroseconds(2);
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trig, LOW);// 10ms만큼 출력
 
  unsigned long duration = pulseIn(echo, HIGH);
 
  // 초음파의 속도는 초당 340미터를 이동하거나, 29마이크로초 당 1센치를 이동합니다.
  // 따라서, 초음파의 이동 거리 = duration(왕복에 걸린시간) / 29 / 2 입니다.
  float distance = duration / 29.0 / 2.0;
 
  // 측정된 거리 값를 시리얼 모니터에 출력합니다.
  Serial.print(distance);
  Serial.println("cm");
     tone(piezo, 423);
    delay(distance*5);
    noTone(piezo);
    delay(distance*5);

  if (distance < 20) {
    for (int i = 0; i < numTones; i++) {
      //numTones(8)의 수만큼 반복 실행합니다.
      // tone함수를 통해 피에조부저에서 소리가 나며 tones[]배열에 있는 주파수에 해당하는 음계가 출력됩니다.
      tone(piezo, tones[i]);
      // 0.5초 동안 대기합니다.
      delay(500);
    }
    // 피에조 부저가 연결된 핀으로부터 square-ware를 생성을 중단하도록 설정합니다.
    noTone(piezo);
  }
  // 0.2초 동안 대기합니다.
//  delay(200);
}


/*
  제목    : 초음파센서로 거리 측정하기
  내용   : 초음파센서로부터 10cm 이내로 물체가 감지되었을때 LED가 켜지도록 만들어 봅시다.
*/

// 초음파센서의 송신부를 8번핀으로 선언하고 수신부는 9번핀으로 선언합니다.
int trig = 12;
int echo = 13;

// LED를 A0핀으로 설정합니다.
int led = 26;

// FND
#define FND_A 52
#define FND_B 48
#define FND_C 45
#define FND_D 43
#define FND_E 42
#define FND_F 51
#define FND_G 46
#define FND_DP 44
#define FND_D1 53
#define FND_D2 50
#define FND_D3 49
#define FND_D4 47
int fndPort[8] = {FND_A, FND_B, FND_C, FND_D, FND_E, FND_F, FND_G, FND_DP};
int digit1[2] = {FND_D4, FND_D3};
int digit2[2] = {FND_D2, FND_D1};
int fndData[10][8] = {
  { 1, 1, 1, 1, 1, 1, 0, 0}, // 0
  { 0, 1, 1, 0, 0, 0, 0, 0}, // 1
  { 1, 1, 0, 1, 1, 0, 1, 0}, // 2
  { 1, 1, 1, 1, 0, 0, 1, 0}, // 3
  { 0, 1, 1, 0, 0, 1, 1, 0}, // 4
  { 1, 0, 1, 1, 0, 1, 1, 0}, // 5
  { 1, 0, 1, 1, 1, 1, 1, 0}, // 6
  { 1, 1, 1, 0, 0, 1, 0, 0}, // 7
  { 1, 1, 1, 1, 1, 1, 1, 0}, // 8
  { 1, 1, 1, 1, 0, 1, 1, 0}, // 9
};

// 실행시 가장 먼저 호출되는 함수이며, 최초 1회만 실행됩니다.
// 변수를 선언하거나 초기화를 위한 코드를 포함합니다.
void setup() {
  // 초음파센서의 동작 상태를 확인하기 위하여 시리얼 통신을 설정합니다. (전송속도 9600bps)
  Serial.begin(9600);
  //초음파 송신부-> OUTPUT, 초음파 수신부 -> INPUT,  LED핀 -> OUTPUT
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);

  // FND
  for (int idx = 0 ; idx < 8 ; idx++)
  {
    pinMode(fndPort[idx], OUTPUT);
  }
  for ( int jdx = 0; jdx < 2; jdx++)
  {
    pinMode(digit1[jdx], OUTPUT);
    pinMode(digit2[jdx], OUTPUT);
  }
}

// setup() 함수가 호출된 이후, loop() 함수가 호출되며,
// 블록 안의 코드를 무한히 반복 실행됩니다.
void loop() {
  //digitalWrite(trig, LOW);
  //digitalWrite(echo, LOW);
  //delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);

  // 초음파의 속도는 초당 340미터를 이동하거나, 29마이크로초 당 1센치를 이동합니다.
  // 따라서, 초음파의 이동 거리 = duration(왕복에 걸린시간) / 29 / 2 입니다.
  float distance = duration / 58.8;
  }
  // 측정된 거리 값를 시리얼 모니터에 출력합니다.
  Serial.print(distance);
  Serial.print(" : ");
  Serial.println(duration*340/20000);
  /*
    if (dist > 99) {
      digitalWrite(digit1[0], 1);
      digitalWrite(digit1[1], 1);
      digitalWrite(digit2[0], 0);
      digitalWrite(digit2[1], 1);
      for (int jdx = 0; jdx < 7; jdx++)
      {
        digitalWrite(fndPort[jdx], fndData[dist / 100][jdx]);
      }
      delayMicroseconds(20000);
    }

  */
  if (dist > 9) {
    digitalWrite(digit1[0], 1);
    digitalWrite(digit1[1], 0);
    digitalWrite(digit2[0], 1);
    digitalWrite(digit2[1], 1);
    for (int idx = 0; idx < 7; idx++)
    {
      digitalWrite(fndPort[idx], fndData[dist / 10][idx]);
    }
    delayMicroseconds(2000);
  }

  digitalWrite(digit1[0], 0);
  digitalWrite(digit1[1], 1);
  digitalWrite(digit2[0], 1);
  digitalWrite(digit2[1], 1);
  for (int jdx = 0; jdx < 7; jdx++)
  {
    digitalWrite(fndPort[jdx], fndData[dist % 10][jdx]);
  }
  delayMicroseconds(20000);
}


//시계
#include <MsTimer2.h>
int hour = 0, minute = 0, second = 0;

//센서 구동에 필요한 헤더 파일들
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

///IMU

//mpu 라이브러리 생성
MPU6050 mpu;

//인터럽트핀 D3(INT5)
#define INTERRUPT_PIN 2

// IMU 데이터 위한 변수들
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float tiltVal = 0;

//인터럽트 변수
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high

// IMU 센서 상태들을 저장할 변수들
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPUN
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer



/// FND
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
#define FND_D4 47 // Segment A to G, DP, Digit 1 to 4

#define SW_FND 37 // FND 표시 제어 스위치, 누를 때마다 fndState 값 1~3으로 변경

int fndIndVal = 0; // FND 표시값
int fndState = 1; // 1~3의 범위를 가지며, 각 값마다 fndIntVal이 바뀜
// 1 : 기울기
// 2 : 인터럽트 카운트
// 3 : 초음파 센서로 측정한 거리

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

///Ultrasonic
#define trig 12 // 송신부
#define echo 13 // 수신부
unsigned long duration = 0; // 초음파가 되돌아 오는데 걸리는 시간
int distance = 0; // distance = duration / 29.0 / 2.0;
int predistance = 0; // 거리가 100 이상일 경우 제어

void setup() {
  //I2C 세팅 및 시작
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  Serial.begin(115200);
  while (!Serial);

  // mpu 센서 초기화
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  // DMP(Digital Motion Processor) 초기화
  devStatus = mpu.dmpInitialize();

  // 초기 감도 세팅
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

  // DMP 활성화
  mpu.setDMPEnabled(true);

  // IMU 서비스 루틴 작동
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
  mpuIntStatus = mpu.getIntStatus();

  // DMP 사용 가능
  dmpReady = true;

  // FIFO 패킷 사이즈 가져오기
  packetSize = mpu.dmpGetFIFOPacketSize();

  //Fnd
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

// IMU 인터럽트 발생 시 루틴
void dmpDataReady() {
  mpuInterrupt = true;
}

void loop() {
  IMU();
  Fnd();
}

void IMU() {
  // 초기화 실패시 함수 종료
  if (!dmpReady) return;

  // 인터럽트 대기
  while (!mpuInterrupt && fifoCount < packetSize) {
  }

  // 인터럽트 변수 초기화
  mpuInterrupt = false;
}


// 스위치 값마다 FND 표시 값 달라짐
void Fnd() {
  Serial.println(fndState);
  if (digitalRead(SW_FND) == HIGH) {
    while (digitalRead(SW_FND) == LOW) {
      fndState ++;
    }
    //delay(500);
    if (fndState > 3) {
      fndState = 1;
    }
  }
  if (fndState == 1) {
    if (tiltVal < 0) {
      fndIndVal = tiltVal * (-1);
    }
    else {
      fndIndVal = tiltVal;
    }
  }
  else if (fndState == 2) {
  }
  else if (fndState == 3) {
  }
  digitalWrite(digit1[0], 1);
  digitalWrite(digit1[1], 1);
  digitalWrite(digit2[0], 1);
  digitalWrite(digit2[1], 0);
  for (int idx = 0; idx < 7; idx++)
  {
    digitalWrite(fndPort[idx], fndData[fndState][idx]);
  }
  delayMicroseconds(8000);

  if (fndIndVal > 9) {
    digitalWrite(digit1[0], 1);
    digitalWrite(digit1[1], 0);
    digitalWrite(digit2[0], 1);
    digitalWrite(digit2[1], 1);
    for (int idx = 0; idx < 7; idx++)
    {
      digitalWrite(fndPort[idx], fndData[fndIndVal / 10][idx]);
    }
    delayMicroseconds(8000);
  }
  digitalWrite(digit1[0], 0);
  digitalWrite(digit1[1], 1);
  digitalWrite(digit2[0], 1);
  digitalWrite(digit2[1], 1);
  for (int jdx = 0; jdx < 7; jdx++)
  {
    digitalWrite(fndPort[jdx], fndData[fndIndVal % 10][jdx]);
  }
  delayMicroseconds(8000);
}

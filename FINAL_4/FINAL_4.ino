
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

///LED 제어에 필요한 변수들
#define SW_DOWN 34 // 작동 시 점등 간격 느려짐
#define SW_UP 35 // 작동 시 점등 간격 빨라짐
#define SW_TOGGLE 36 // 작동 시 LED 작동/미작동 상태 변화

#define GEN_SIGNAL 5 // LED 작동 시 클락 시그널 발생
#define KEY_UP 2 // SW_UP 작동시 Key
#define KEY_DOWN 1 // SW_DOWN 작동시 Key
#define KEY_TOGGLE 3 // SW_TOGGLE 작동시 Key

int ledSelPortA = 0;
int ledSelPortC = 0;
unsigned long curTimeMs = 0;
int ledShiftInterval = 50;
int signalCount = 0;
int signalCountPerSec = 0;
int ledState = 1;
int ledIntervalKey = 0;
int ledIntervalTilt = 0;
int keyFlag;


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

int fndSwFlag; // FND 스위치 눌렀을 때 한 번만 작동
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

///부저
#define BUZZER_PIN 6 // 6 : BLUE LED, 9 : BUZZER //

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

  // DMP 서비스 루틴 작동
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
  //타이머
  MsTimer2::set(1000, Clocks);
  MsTimer2::start();

  //LED 작동시 클락 발생 시킬 핀
  pinMode(GEN_SIGNAL, OUTPUT);

  //LED 인터럽트 클락 발생시 서비스 루틴
  attachInterrupt(digitalPinToInterrupt(3), Count_Clock, RISING);

  // LED 레지스터 및 시간 설정
  DDRA = 0xF0;
  DDRC = 0xF0;
  curTimeMs = millis();
}

// DMP 인터럽트 발생 시 루틴
void dmpDataReady() {
  mpuInterrupt = true;
}

// 클락 인터럽트 발생 시 루틴
void Count_Clock() {
  signalCount++;
}

void loop() {
  DMP();
  Ultrasonic();
  Clock_Signal();
  Led_Shift();
  Fnd();
  Buzz_Timer();
}

void DMP() {
  // 초기화 실패시 함수 종료
  if (!dmpReady) return;

  // 인터럽트 대기
  while (!mpuInterrupt && fifoCount < packetSize) {
  }

  // 인터럽트 변수 초기화
  mpuInterrupt = false;
  // MPU 상태 읽기
  mpuIntStatus = mpu.getIntStatus();
  // FIFO 버퍼 개수 얻기
  fifoCount = mpu.getFIFOCount();
  // FIFO 오버플로우 시
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    // FIFO 초기화
    mpu.resetFIFO();

    // DMP 데이터 체크
  } else if (mpuIntStatus & 0x02) {
    // packetSize만큼 FIFO가 들어올 때까지 대기
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

    // 데이터 받아오기
    mpu.getFIFOBytes(fifoBuffer, packetSize);

    // 사용 가능한 패킷이 1개 이상인 경우 FIFO 수를 추적
    // 이를 통해 인터럽트를 기다리지 않고 즉시 더 많은 것을 읽을 수 있음
    fifoCount -= packetSize;

    //센서 값을 각도로 표시
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    tiltVal = (ypr[2] * 180 ) / M_PI;

    //출력
    /*
        Serial.print("ypr\t");
        Serial.print(ypr[0] * 180 / M_PI);
        Serial.print("\t");
        Serial.print(ypr[1] * 180 / M_PI);
        Serial.print("\t");
        Serial.println(ypr[2] * 180 / M_PI);
        //Serial.println(tiltVal);
    */
  }
}

// 초음파 센서. 초음파 발생 후 수신까지 걸린 시간을 계산하여 값 출력
// 100cm 이상일 경우 이전 값 출력
void Ultrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(10);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH,5800);
  distance = duration / 29.0 / 2.0;
  /*
  if (distance > 100) {
    distance = predistance;
  }
  predistance = distance;
  */
}

// LED 2개 작동 마다 클락 신호 1번 발생
void Clock_Signal() {
  if (PORTA == 0x10 || PORTA == 0x40 || PORTC == 0x80 || PORTC == 0x20) {
    digitalWrite(GEN_SIGNAL, HIGH);
  }
  else {
    digitalWrite(GEN_SIGNAL, LOW);
  }
}

// 시계
void Clocks() {
  second++;
  if (second == 60)
  {
    second = 0;
    minute++;
  }
  if (minute == 60)
  {
    minute = 0;
    hour++;
  }
  signalCountPerSec = signalCount;
  /*
    Serial.print(hour);
    Serial.print(" : ");
    Serial.print(minute);
    Serial.print(" : ");
    Serial.print(second);
    Serial.print(", ");
    Serial.print(signalCount);
    Serial.print(", ");
    Serial.print(distance);
    Serial.println("cm");
  */
  signalCount = 0;
}

void Led_Shift() {
  Key();
  Led_Interval_Control();
  ledIntervalTilt = (tiltVal / 2);
  if (ledState == 0) {
  } // ledState가 0일 경우 작동 중지
  if (ledState == 1) {
    if (ypr[2] * 180 / M_PI <= 0) {
      ledShiftInterval = 50 + (ledIntervalTilt / 2) + ledIntervalKey;
      if (curTimeMs + ledShiftInterval < millis())
      {
        PORTA = 0x00;
        PORTC = 0x00;
        PORTA = 0x10 << ledSelPortA;
        ledSelPortA++;
        curTimeMs = millis() ;
        if (ledSelPortA > 4) {
          PORTA = 0x00;
          PORTC = 0x80 >> ledSelPortC;
          ledSelPortC++;
          curTimeMs = millis() ;
          if ( ledSelPortC > 4)
          {
            PORTC = 0x00;
            ledSelPortA = 0;
            ledSelPortC = 0;
          }
        }
      }
    }
    else {
      ledShiftInterval = 50 - (ledIntervalTilt / 2) + ledIntervalKey;
      if (curTimeMs + ledShiftInterval < millis())
      {
        PORTA = 0x00;
        PORTC = 0x00;
        PORTC = 0x10 << ledSelPortC;
        ledSelPortC++;
        curTimeMs = millis() ;
        if (ledSelPortC > 4) {
          PORTC = 0x00;
          PORTA = 0x80 >> ledSelPortA;
          ledSelPortA++;
          curTimeMs = millis() ;
          if ( ledSelPortA > 4)
          {
            PORTA = 0x00;
            ledSelPortA = 0;
            ledSelPortC = 0;
          }
        }
      }
    }
  }
}

// 센서 값 별 LED 점등 시간 설정
// 총 점등 간격 최대 90, 최소 10
// Key로 제어한 점등 간격은 최대 40, 최소 -40
// LED 제어
void Led_Interval_Control() {
  if (ledShiftInterval >= 90)
    ledShiftInterval = 90;
  else if (ledShiftInterval <= 10)
    ledShiftInterval = 10;
  if (ledIntervalKey >= 40) {
    ledIntervalKey = 40;
  }
  else if (ledIntervalKey <= -40) {
    ledIntervalKey = -40;
  }
}

// Key 제어를 위해 Key 값 설정
int Led_Key_Input() {
  int Key_In = 0;
  if (digitalRead(SW_DOWN) == HIGH) {
    if (keyFlag == 0) {
      Key_In = KEY_DOWN;
    }
  }

  if (digitalRead(SW_UP) == HIGH) {
    if (keyFlag == 0) {
      Key_In = KEY_UP;
    }
  }
  if (digitalRead(SW_TOGGLE) == HIGH) {
    if (keyFlag == 0) {
      Key_In = KEY_TOGGLE;
    }
  }
  else if((digitalRead(SW_DOWN) == LOW)&&(digitalRead(SW_UP) == LOW)&&(digitalRead(SW_TOGGLE) == LOW)){
    keyFlag = 0;
  }
  return Key_In;
}

int Key() {
  int Key = 0;
  Key = Led_Key_Input();
  switch (Key) {
    case KEY_DOWN : // LED Speed Down
      ledIntervalKey += 10;
      keyFlag = 1;
      break;
    case KEY_UP : // LED Speed Up
      ledIntervalKey -= 10;
      keyFlag = 1;
      break;
    case KEY_TOGGLE : // LED Toggle
      ledState = !ledState;
      keyFlag = 1;
      break;
  }

  //Serial.println(ledShiftInterval);
}

// 스위치 값마다 FND 표시 값 달라짐
void Fnd() {
  if (digitalRead(SW_FND) == HIGH) {
    if (fndSwFlag == 0) {
      fndState ++;
      if (fndState > 3) {
        fndState = 1;
      }
      fndSwFlag = 1;
    }
    //else if (fndSwFlag == 1) {
    //}
  }
  else {
    fndSwFlag = 0;
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
    fndIndVal = signalCountPerSec;
  }
  else if (fndState == 3) {
    fndIndVal = distance;
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

// 10초 마다 부저 울림
void Buzz_Timer() {
  if (second % 10 == 0) {
    digitalWrite(BUZZER_PIN, HIGH); // periodly BUZZER
  }
  Buzz_Stop();
}

// 1초마다 부저 꺼짐
void Buzz_Stop() {
  if (second % 10 == 1) {
    digitalWrite(BUZZER_PIN, LOW);
  }
}

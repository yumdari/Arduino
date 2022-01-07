//IMU_LED_US_ORIGIN_4
//동작 확인 및 시리얼 출력문 삭제

//시계
#include <MsTimer2.h>
int hour = 0, minute = 0, second = 0;

//센서 구동에 필요한 헤더 파일들
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

//mpu 라이브러리 생성
MPU6050 mpu;

//인터럽트핀 D3(INT5)
#define INTERRUPT_PIN 2

//LED 제어에 필요한 변수들
#define SW_DOWN 34
#define SW_UP 35
#define SW_TOGGLE 36
#define BUZZER_PIN 6 // 6 : BLUE LED, 9 : BUZZER
#define GEN_SIGNAL 5
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_TOGGLE 3
int ledSelPortA = 0;
int ledSelPortC = 0;
unsigned long curTimeMs = 0;
int ledShiftInterval = 50;
int signalCount = 0;
int signalCountPerSec = 0;
int ledState = 1;
int keyState = 1;
int temp = 0;
int ledIntervalKey = 0;
int ledIntervalTilt = 0;

// 센서 상태들을 저장할 변수들
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPUN
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// 최종 값을 위한 변수들
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float tiltVal;

//인터럽트 변수
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high

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

//Ultrasonic
// 초음파센서의 송신부를 12번핀으로 선언하고 수신부는 13번핀으로 선언합니다.
#define trig 12
#define echo 13
unsigned long duration = 0;
float distance = 0;
int dist = 0;


//인터럽트 발생 시 루틴
void dmpDataReady() {
  mpuInterrupt = true;

  Serial.println(ledShiftInterval);
  //Led_Interval_Control();
}

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

  // 초기화가 잘 되었다면
  //if (devStatus == 0) {
  // DMP 활성화
  //Serial.println(F("Enabling DMP..."));
  mpu.setDMPEnabled(true);

  // LOW -> HIGH 일 때 서비스 루틴 작동
  //Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
  mpuIntStatus = mpu.getIntStatus();

  // DMP 사용 가능
  //Serial.println(F("DMP ready! Waiting for first interrupt..."));
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

  //Timer
  MsTimer2::set(1000, Clocks);
  MsTimer2::start();
  // LED 레지스터 및 시간 설정
  DDRA = 0xF0;
  DDRC = 0xF0;
  attachInterrupt(digitalPinToInterrupt(3), Count_Clock, RISING);
  curTimeMs = millis();
}

/*
  void Ultrasonic() {
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration / 29.0 / 2.0;
  if (distance < 50) {
    dist = distance;
  }
  Serial.println(dist);
  }
*/

void Fnd() {
  if (ledShiftInterval > 9) {
    digitalWrite(digit1[0], 1);
    digitalWrite(digit1[1], 0);
    digitalWrite(digit2[0], 1);
    digitalWrite(digit2[1], 1);
    for (int idx = 0; idx < 7; idx++)
    {
      digitalWrite(fndPort[idx], fndData[ledShiftInterval / 10][idx]);
    }
    delayMicroseconds(8000);
  }
  digitalWrite(digit1[0], 0);
  digitalWrite(digit1[1], 1);
  digitalWrite(digit2[0], 1);
  digitalWrite(digit2[1], 1);
  for (int jdx = 0; jdx < 7; jdx++)
  {
    digitalWrite(fndPort[jdx], fndData[ledShiftInterval % 10][jdx]);
  }
  delayMicroseconds(8000);
}

int Key() {
  int Key = 0;
  Key = Key_Input();
  switch (Key) {
    case KEY_DOWN : // LED Speed Down
      ledIntervalKey = 5;

      break;
    case KEY_UP : // LED Speed Up
      ledIntervalKey = -5;

      break;
    case KEY_TOGGLE : // LED Toggle
      ledState = ! ledState;
      break;
  }
}

// 센서 값 별 LED 점등 시간 설정
void Led_Interval_Control() {
  ledIntervalTilt = tiltVal / 2;
  if (tiltVal >= 0) {
    ledShiftInterval = ledShiftInterval + ledIntervalKey - ledIntervalTilt;
  }
  else if {
  ledShiftInterval = ledShiftInterval + ledIntervalKey + ledIntervalTilt;
}
ledIntervalKey = 0;
ledIntervalTilt = 0;
if (ledShiftInterval > 90)
    ledShiftInterval = 90;
  else if (ledShiftInterval < 10)
    ledShiftInterval = 10;
}


void Led_Shift() {
  // LED 제어
  if (ledState) {
    Led_Interval_Control();
    if (ypr[2] * 180 / M_PI <= 0) {
      if (curTimeMs + ledShiftInterval < millis())
      {
        PORTA = 0x00;
        PORTC = 0x00;
        Key();
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
    else if (curTimeMs + ledShiftInterval < millis())
    {
      PORTA = 0x00;
      PORTC = 0x00;
      Key();
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

void loop() {
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
    //if (millis() % 5 == 0) {
    //Key();
    //}
    Led_Shift();
    Clock_Signal();
    //Ultrasonic();
    Fnd();
    Buzz_Timer();
  }
}

int Key_Input() {
  int Key_In = 0;
  temp = ledShiftInterval;
  if (digitalRead(SW_DOWN) == HIGH) {
    Key_In = KEY_DOWN;
  }
  if (digitalRead(SW_UP) == HIGH) {
    Key_In = KEY_UP;
  }
  if (digitalRead(SW_TOGGLE) == HIGH) {
    Key_In = KEY_TOGGLE;
  }
  return Key_In;
}

void Buzz_Timer() {
  if (second % 10 == 0) {
    digitalWrite(BUZZER_PIN, HIGH); // periodly BUZZER
  }
  Buzz_Stop();
}

void Buzz_Stop() {
  if (second % 10 == 1) {
    digitalWrite(BUZZER_PIN, LOW);
  }
}

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
    Serial.println(second);
    signalCount = 0;
  */
}// 1 sec clock

void Clock_Signal() {
  if (PORTA == 0x10 || PORTA == 0x40 || PORTC == 0x80 || PORTC == 0x20) {
    digitalWrite(GEN_SIGNAL, HIGH);
  }
  else {
    digitalWrite(GEN_SIGNAL, LOW);
  }
}

void Count_Clock() {
  signalCount++;
}

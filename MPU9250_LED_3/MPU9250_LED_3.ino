//센서 구동에 필요한 헤더 파일들
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69

//mpu 라이브러리 생성
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high

#define OUTPUT_READABLE_YAWPITCHROLL

//인터럽트핀 D3(INT5)
#define INTERRUPT_PIN 3

//LED 제어에 필요한 변수들
#define LED_SHIFT
int ledSelPortA = 0;
int ledSelPortC = 0;
unsigned long curTimeMs = 0;
int ledShiftInterval = 50;

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


//인터럽트 변수
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high

//인터럽트 발생 시 루틴
void dmpDataReady() {
  mpuInterrupt = true;
}

void setup() {
  //I2C 세팅 및 시작
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  // initialize serial communication
  // (115200 chosen because it is required for Teapot Demo output, but it's
  // really up to you depending on your project)
  Serial.begin(115200);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  // NOTE: 8MHz or slower host processors, like the Teensy @ 3.3v or Ardunio
  // Pro Mini running at 3.3v, cannot handle this baud rate reliably due to
  // the baud timing being too misaligned with processor ticks. You must use
  // 38400 or slower in these cases, or use some kind of external separate
  // crystal solution for the UART timer.

  // mpu 센서 초기화
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  // 연결 확인
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  /// wait for ready
  //Serial.println(F("\nSend any character to begin DMP programming and demo: "));
  //while (Serial.available() && Serial.read()); // empty buffer
  //while (!Serial.available());                 // wait for data
  //while (Serial.available() && Serial.read()); // empty buffer again

  // DMP(Digital Motion Processor) 초기화
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();

  // 초기 감도 세팅
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

  // 초기화가 잘 되었다면
  if (devStatus == 0) {
    // DMP 활성화
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);

    // LOW -> HIGH 일 때 서비스 루틴 작동
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    // DMP 사용 가능
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;

    // FIFO 패킷 사이즈 가져오기
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = 초기화 에러
    // 2 = DMP 업데이트 에러
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }

  // LED 레지스트 및 시간 설정
  DDRA = 0xF0;
  DDRC = 0xF0;
  curTimeMs = millis();
}


// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================


// 센서 값 별 LED 점등 시간 설정
void Led_Interval_Control() {
  if (60 < ypr[1] * 180 / M_PI && ypr[1] * 180 / M_PI <= 90) {
    ledShiftInterval = 10;
  }
  else if (30 < ypr[1] * 180 / M_PI && ypr[1] * 180 / M_PI <= 60) {
    ledShiftInterval = 45;
  }
  else if (-30 < ypr[1] * 180 / M_PI && ypr[1] * 180 / M_PI <= 30) {
    ledShiftInterval = 50;
  }
  else if (-60 < ypr[1] * 180 / M_PI && ypr[1] * 180 / M_PI <= -30) {
    ledShiftInterval = 65;
  }
  else
    //if
    //(-90 < ypr[1] * 180 / M_PI && ypr[1] * 180 / M_PI <= -60)
  {
    ledShiftInterval = 90;
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
    Serial.println(F("FIFO overflow!"));

    // DMP 데이터 체크
  } else if (mpuIntStatus & 0x02) {
    // packetSize만큼 FIFO가 들어올 때까지 대기
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

    // 데이터 받아오기
    mpu.getFIFOBytes(fifoBuffer, packetSize);

    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;

    //값 얻어오기
#ifdef OUTPUT_READABLE_YAWPITCHROLL
    // 오일러 각을 각도로 표시
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    //출력
    Serial.print("ypr\t");
    Serial.print(ypr[0] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[1] * 180 / M_PI);
    Serial.print("\t");
    Serial.println(ypr[2] * 180 / M_PI);
#endif

    // LED 제어
#ifdef LED_SHIFT
    if (curTimeMs + ledShiftInterval < millis())
    {
      Led_Interval_Control();
      PORTA = 0x10 << ledSelPortA;
      ledSelPortA++;
      curTimeMs = millis() ;
      if (ledSelPortA > 4) {
        Led_Interval_Control();
        PORTC = 0x80 >> ledSelPortC;
        ledSelPortC++;
        curTimeMs = millis() ;
        if ( ledSelPortC > 4)
        {
          ledSelPortA = 0;
          ledSelPortC = 0;
        }
      }
    }
#endif
  }
}

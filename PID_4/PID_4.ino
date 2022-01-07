//PID constants
#include <MsTimer2.h>

#define TRIG 12 // 송신부
#define ECHO 13 // 수신부

#define dcFront 2 // front
#define dcRear 3 // rear

unsigned long duration = 0; // 초음파가 되돌아 오는데 걸리는 시간
int distance = 0; // distance = duration / 29.0 / 2.0;

double kp = 2;
double ki = 5; // 5
double kd = 1; // 1

unsigned long currentTime = 0, previousTime = 0;
double elapsedTime = 0;
double error = 0;
double lastError = 0;
double input = 0, output = 0, setPoint = 0, result = 0;
double cumError = 0, rateError = 0;

unsigned int serial_input_value = 0;

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

void setup() {
  Serial.begin(9600);
  setPoint = 10; //set point at zero degrees

  for (int idx = 0 ; idx < 8 ; idx++)
  {
    pinMode(fndPort[idx], OUTPUT);
  }
  for ( int jdx = 0; jdx < 2; jdx++)
  {
    pinMode(digit1[jdx], OUTPUT);
    pinMode(digit2[jdx], OUTPUT);
  }

  pinMode(dcFront, OUTPUT);
  pinMode(dcRear, OUTPUT);

  MsTimer2::set(1000, mortor);
  MsTimer2::start();

}
void loop() {
  ultrasonicFunction();
  fndIndication();
  mortor();
}

void mortor() {
  int frontSpeed, rearSpeed;
  if (distance > 10) {
    frontSpeed = map(distance, 0, 15, 0, 255);
    analogWrite(dcFront, frontSpeed);
    analogWrite(dcRear, 0);
  }
  else if (distance < 10) {
    rearSpeed = map(distance, 5, 0, 0, 255);
    analogWrite(dcFront, 0);
    analogWrite(dcRear, rearSpeed);
  }
}

/*
  void calculation() {
  input = distance; //read from rotary encoder connected to A0
  output = computePID(input);
  //result = input + output;

  Serial.println(output);
  //delay(100);
  int outputVal = map (distance, 10, 0, 0, 85);
  analogWrite(dcRear, outputVal);
  //analogWrite(3, output); //control the motor based on PID value
  }*/

/*
  void motorPID(){    //10ms마다 호출

    speedActualLeft = (leftMotorEncoder - leftMotorEncoderPrevPID)*60*(1000/LOOPTIME)/4200;

  //속도를 RPM으로 측정하는 코드 : Encoder의 현재값에서 이전값을 뺀후, 측정 시간으로 나누고 Pulse 수 등을 사용해서 RPM 으로 변환한다.   LOOPTIME이 PID 제어가 동작하는 주기이다 (나의 경우는 10ms)

    leftMotorEncoderPrevPID = leftMotorEncoder;     //현재 엔코더 값을 다음에 사용하도록 저장
    error = (speedRequestLeft) - (speedActualLeft);    //에러량을 계산
    iTermLeft += (Ki * error);                                 //I 항의 경우 누적해야 하므로 별도로 저장
    pidTerm = (Kp * error) + (Kd * (error - lastErrorLeft)) + iTermLeft; //전체 PID 값을 계산

    lastErrorLeft = error;                                      //현재 에러 값을 다음에 사용하도록 저장
    leftControl = constrain(abs(pidTerm), 0, 255) * ((pidTerm <0)?-1:1);   //PID 텀을 모터 제어에 사용되는 값의 범위인 0~255의 값으로 변환하는 함수
    LeftMotor_PID( (leftControl>=0)? 1:0, abs(leftControl));   //실제 모터의 PWM 값으로 출력하는 함수
  }
*/

double computePID(double inp) {
  currentTime = millis(); //get current time
  elapsedTime = (double)(currentTime - previousTime); //compute time elapsed from previous computation
  error = setPoint - inp; // determine error
  cumError += error * elapsedTime; // compute integral
  rateError = (error - lastError) / elapsedTime; // compute derivative
  double out = kp * error + ki * cumError + kd * rateError; //PID output
  lastError = error; //remember current error
  previousTime = currentTime; //remember current time
  return out; //have function return the PID output
}

void serialEvent() {
  if (Serial.available() > 0) {
    serial_input_value = Serial.parseInt();
    input += serial_input_value;
    //Serial.println(serial_input_value);
  }
}

void ultrasonicFunction() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(10);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH, 5880);
  distance = duration / 58.8;
}

void fndIndication() {
  if (distance > 9) {
    digitalWrite(digit1[0], 1);
    digitalWrite(digit1[1], 0);
    digitalWrite(digit2[0], 1);
    digitalWrite(digit2[1], 1);
    for (int idx = 0; idx < 7; idx++)
    {
      digitalWrite(fndPort[idx], fndData[distance / 10][idx]);
    }
    delayMicroseconds(8000);
  }
  digitalWrite(digit1[0], 0);
  digitalWrite(digit1[1], 1);
  digitalWrite(digit2[0], 1);
  digitalWrite(digit2[1], 1);
  for (int jdx = 0; jdx < 7; jdx++)
  {
    digitalWrite(fndPort[jdx], fndData[distance % 10][jdx]);
  }
  delayMicroseconds(8000);
}

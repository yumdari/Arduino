//PID constants
#include <MsTimer2.h>

#define TRIG 12 // 송신부
#define ECHO 13 // 수신부

#define IN1 2 // front
#define IN2 3 // rear

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

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  MsTimer2::set(1000, calculation);
  MsTimer2::start();

}
void loop() {
  ultrasonicFunction();
  fndIndication();
}

void calculation() {
  input = distance; //read from rotary encoder connected to A0
  output = computePID(input);
  //result = input + output;
 
  Serial.println(output);
  //delay(100);
  //analogWrite(IN1, 10)
  //analogWrite(3, output); //control the motor based on PID value
}

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
  fndIndVal = distance;
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

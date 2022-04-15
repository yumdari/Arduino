//PID constants

double kp = 2;
double ki = 5;
double kd = 1;

unsigned long currentTime = 0, previousTime = 0;
double elapsedTime = 0;
double error = 0;
double lastError = 0;
double input = 0, output = 0, setPoint = 0, result = 0;
double cumError = 0, rateError = 0;

unsigned int serial_input_value = 0;

void setup() {
  Serial.begin(9600);
  setPoint = 0; //set point at zero degrees
}
void loop() {
  input += 1; //read from rotary encoder connected to A0
  output = computePID(input);
  result = input + output;
  //delay(100);
  Serial.println(result);
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

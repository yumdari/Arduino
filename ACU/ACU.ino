#define SW_RIGHT 
#define SW_LEFT 
int inputValue = analogRead(A0);
int convertedValue = map(inputValue, 0, 1023, 0, 255);


void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  analogWrite(IN1, convertedValue);
  analogWrite(IN2, 0);
  Serial.println(convertedValue);
  delay(100);
}

 # define TRIG 5
 # define ECHO 6
 # define PIRINPUT 2
 # define BUZZERPIN 3

int pirState = 0; // PIR sensor variables

unsigned long duration = 0; // 초음파가 되돌아 오는데 걸리는 시간
unsigned int distance = 0; // distance = duration / 29.0 / 2.0;

void PirFunction() {
    pirState = !pirState;
}

void setup() {
    DDRB = B00111000; // set 11, 12, 13 pins up to output

    Serial.begin(9600);

    pinMode(PIRINPUT, INPUT);

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    
    attachInterrupt(0, PirFunction, RISING); //

    pinMode(BUZZERPIN, OUTPUT);
}

void BUZZER(){
  tone(BUZZERPIN, 131);
  delay(100);
  noTone(BUZZERPIN);
  delay(100);
}

void UltrasonicFunction() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(10);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    
    int duration = pulseIn(ECHO, HIGH);
    
    distance = duration / 29.0 / 2.0;
    Serial.println(distance);

//    if(distance <= 20){
//      BUZZER;
//    }
}

void LedFunction() {
      PORTB = B00100000; // 13, Red LED
      delay(1000);
      PORTB = B00010000; // 12, Green LED
      delay(1000);
      PORTB = B00001000; // 11, Blue LED
      delay(1000);
}

void loop() {
    PirFunction();
    UltrasonicFunction();
    LedFunction();
        BUZZER;
}

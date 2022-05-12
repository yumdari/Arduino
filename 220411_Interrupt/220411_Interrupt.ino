volatile byte state = HIGH;
const int duration = 1000;
unsigned long pre_time = 0;
unsigned long cur_time = 0;

void setup() {
  
  attachInterrupt(0, isr, FALLING);
  pinMode(13, OUTPUT);  
  Serial.begin(9600);
}

void isr(){
  cur_time = millis();
  if(cur_time - pre_time >= duration){
    Serial.println("인터럽트");
    pre_time = cur_time;
  }
}

void loop() {

}

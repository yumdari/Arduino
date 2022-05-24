#define LED 13

void setup(){
  Serial.begin(9600);
  pinMode(LED, INPUT);
}

void loop(){
  if(Serial.available()>0){
    int data = Serial.read();
    Serial.println(data); // echo
    if(data == '1')
    digitalWrite(LED, HIGH);
    delay(1000);
  }
  else
  digitalWrite(LED, LOW);
  delay(1000);
}

void setup(){
  Serial.begin(9600);
  pinMode(13, INPUT);
}

void loop(){
  if(Serial.available()>0){
    int data = Serial.read();
    Serial.println(data); // echo
    if(data == '1')
    digitalWrite(13, HIGH);
    delay(1000);
  }
  else
  digitalWrite(13, LOW);
  delay(1000);
}

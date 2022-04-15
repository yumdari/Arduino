unsigned long nowTime=0;
unsigned long preTime=0;
unsigned char buzzState=0;

void setup ()
  {
  pinMode (9, OUTPUT);
  pinMode (26, OUTPUT);
  }  // end of setup

void loop() {
  nowTime = millis();
  if(nowTime - preTime >= 1000)
  {
    preTime = nowTime;
    buzzState=!buzzState;
    analogWrite(9,buzzState);
  }
}

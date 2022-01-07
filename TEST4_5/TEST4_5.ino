long time = millis() ; // 현재까지의 경과시간을 저장합니다 (즉, 0입니다.)
int i = 0;
void setup()
{
  DDRA = 0xF0;
  DDRC = 0xF0;
  Serial.begin(9600);
}

void loop()
{
  if (time + 30 < millis()) //0+1000(1초) < 업로드 후 경과한 시간이 1초가 넘어갈 때
  {
    PORTA = 0x10;
    i++;
    Serial.println(time);
  }
  if (time + 30 < millis()) // 0+2000(2초) < 2초가 넘어갈 때
  {
    PORTA = 0x10 << i ;
    time = millis() ; // 현재까지 경과한 시간을 time에 저장 (2초 저장)
    if (i > 4) {
      i = 0;
    }
    Serial.println(time);
    digitalWrite(26, LOW) ; // LED가 꺼짐
  }
}

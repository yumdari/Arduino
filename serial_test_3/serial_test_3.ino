int led = 26;
char flag = 0;

void setup(){
  Serial.begin(9600);

  pinMode(led, OUTPUT);

  Serial.println("Start LED Control.");
}

void loop(){
  if(flag)  // 만약 flag가 1이면, led On
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);
}

void serialEvent(){
  char ledOnOff;

  ledOnOff = Serial.read();     // 수신 데이터(시리얼 모니터에서 입력한 값) ledOnOff에 저장

  if(ledOnOff == 'o'){          // ledOnOff 값이 'o'이면,
    Serial.println("LED On");   // 시리얼 모니터에 "LED On" 출력하고,
    flag = true;                // flag에 true(1) 저장
  }
  else if(ledOnOff == 'x'){     // ledOnOff 값이 'x'이면,
    Serial.println("LED Off");  // 시리얼 모니터에 "LED Off" 출력하고,
    flag = false;               // flag에 false(0) 저장
  }
}

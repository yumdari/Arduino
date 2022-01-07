int led = 26;

void setup(){
  Serial.begin(9600);

  pinMode(led, OUTPUT);

  Serial.println("Start LED Control.");
}

void loop(){
}

// 시리얼 통신으로 데이터를 송신 받으면 함수 호출
void serialEvent(){
  char ledOnOff;

//ledOnOff = Serial.read() 없이, if(Serial.read() == '')를 바로 사용하면 두, 세번 전송을 해주어야 읽어들이기 때문에 느리다.
  ledOnOff = Serial.read();     // 수신 데이터(시리얼 모니터에서 입력한 값) ledOnOff에 저장

  if(ledOnOff == 'o'){          // ledOnOff 값이 'o'이면,
    digitalWrite(led, HIGH);    // LED On하고
    Serial.println("LED On");   // 시리얼 모니터에 "LED On" 출력
  }
  else if(ledOnOff == 'x'){     // ledOnOff 값이 'x'이면,
    digitalWrite(led, LOW);     // LED Off하고
    Serial.println("LED Off");  // 시리얼 모니터에 "LED Off" 출력
  }
}

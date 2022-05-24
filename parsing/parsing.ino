#include <HardwareSerial.h>
HardwareSerial mySerial(2); //3개의 시리얼 중 2번 채널을 사용

void setup() {
    Serial.begin(115200); //기존의 기본 시리얼
    mySerial.begin(115200, SERIAL_8N1, 12, 13); //추가로 사용할 시리얼. RX:12 / TX:13번 핀 사용
}

void loop() {
    if(mySerial.available() > 0){

       //Serial.println("test");
    char totalGot[50];
    char * totalGotArr[3];
    int index = 0, i = 0;
    char * ptr = NULL;
    
    while(mySerial.available())
    {
      totalGot[index++] = mySerial.read();
    }
    totalGot[index] = '\0';
    
    ptr = strtok(totalGot, "#");

    while (ptr !=NULL)
    {
      totalGotArr[i++] = ptr;
      ptr=strtok(NULL, " ");
    }
    int small = atoi(totalGotArr[0]);
    int big = atoi(totalGotArr[1]);    

  
    Serial.println(small);
    delay(1000);
    Serial.println(big);
    delay(1000);
    print("\n")

      
      //String command = mySerial.readStringUntil('\n'); //추가 시리얼의 값을 수신하여 String으로 저장
//      Serial.parseFloat();
//      String command = mySerial.readString();
//      
//      Serial.println(command); //기본 시리얼에 추가 시리얼 내용을 출력    
//      
    }
}

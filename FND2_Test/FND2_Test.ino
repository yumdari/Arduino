#include <MsTimer2.h>
 
#define segA 52  // 'a' 세그먼트 연결 핀 번호
#define segB 48  // 'b' 세그먼트 연결 핀 번호
#define segC 45  // 'c' 세그먼트 연결 핀 번호
#define segD 43  // 'd' 세그먼트 연결 핀 번호
#define segE 42  // 'e' 세그먼트 연결 핀 번호
#define segF 51  // 'f' 세그먼트 연결 핀 번호
#define segG 46  // 'g' 세그먼트 연결 핀 번호
#define segDP 44 // 'dp' 세그먼트 연결 핀 번호
#define digit1 53 // 1st digit 연결 핀번호
#define digit2 50 // 2nd digit 연결 핀번호
#define digit3 49 // 3rd digit 연결 핀번호
#define digit4 47 // 4th digit 연결 핀번호3r
 
// main 함수에서 처리 편하게 하기 위해 핀번호 배열을 생성
int fndDigit[4] = {digit1, digit2, digit3, digit4};
int fndPort[8] = {segA, segB, segC, segD, segE, segF, segG, segDP};
// index 0-9 -> 숫자 1~9
// index 10 -> Blank
int fndData[11][8] = 
{{0,1,1,1,1,1,1,0},  // MSB   --  LSB
  {0,0,0,0,1,1,0,0},
  {1,0,1,1,0,1,1,0},
  {1,0,0,1,1,1,1,0},
  {1,1,0,0,1,1,0,0},
  {1,1,0,1,1,0,1,0},
  {1,1,1,1,1,0,1,0},
  {0,0,0,0,1,1,1,0},
  {1,1,1,1,1,1,1,0},
  {1,1,0,1,1,1,1,0}};   
// 초기값 10 -> Blank
int iflag = 0;
 
void setup(){
    // 1000ms 간격으로 myTimer() 함수를 호출합니다.
    MsTimer2::set(1000, myTimer);
    MsTimer2::start();
    // 7 Segment 연결된 포트 모두 출력으로 설정
    for(int i = 0 ; i < 4 ; i++)
    {
        pinMode(fndDigit[i], OUTPUT);
        digitalWrite(fndDigit[i], LOW);
    }
    for(int i = 0 ; i < 8 ; i++)
    {
        pinMode(fndPort[i],OUTPUT);
        digitalWrite(fndPort[i],HIGH);
    }
}
 
void loop(){
    static int iCount = 0;
 
    // 타이머 인터럽트가 발생 (iflag=1) 되면 iCount 를 1씩 증가, iCount 값이 10000일 경우 0으로 전환
    if (iflag == 1)
    {
        if (iCount == 10000) {
            iCount = 0;
        }
        else {
            iCount++;
        }
        iflag = 0;
    }
 
    // 4자리수에 각각 입력 될 숫자 입력
    int digit1st = iCount / 1000;
    int digit2nd = iCount % 1000 / 100;
    int digit3rd = iCount % 100 / 10;
    int digit4th = iCount % 10;
    // for 문을 돌리기 위해 배열을 사용
    int digitData[4] = {digit1st, digit2nd, digit3rd, digit4th};
 
    for(int i = 0 ; i < 4 ; i++)
    {
        // 모든 Digit 1~4 핀 Off
        digitalWrite(digit1,LOW);
        digitalWrite(digit2,LOW);
        digitalWrite(digit3,LOW);
        digitalWrite(digit4,LOW);
 
        // 각 Digit 에 맞는 fnd 숫자의 값 입력
        for(int j= 0 ;j<8;j++)
        {
            digitalWrite(fndPort[j], fndData[digitData[i]][j]); 
            // 소수점 구분 점 찍기
            if(i==1) digitalWrite(fndPort[7], 0);
        }
 
        // 해당 Digit On
        digitalWrite(fndDigit[i],HIGH);
        // 밝기 조절을 위해 2ms LED ON 시간 조절
        delay(2);
    }
}
 
// 10ms 간격 타이머 인터럽트
void myTimer(){
    iflag = 1;
}

#include <LiquidCrystal_I2C.h> // LCD를 쓰기위한 라이브러리 포함

#include <MsTimer2.h> // Timer 라이브러리 포함

#define X_INPUT A1 // A1 : 조이스틱 X입력
#define Y_INPUT A0 // A0 : 조이스틱 Y입력

LiquidCrystal_I2C lcd(0x27, 16, 2); // set LCD address to 0x27 for a 16 chars and 2 line display
//address : 0x3F, 0x27

unsigned int level = 0; // 10초마다 레벨 1씩 증가하며, 블록 드랍 스피드도 5씩 증가

//조이스틱 조작 시 채터링 현상 방지를 위한 플래그 변수
// 1일 때 조이스틱 값이 입력되지 않음
int joyStickFlagA = 0; // 왼쪽
int joyStickFlagD = 0; // 오른쪽
int joyStickFlagW = 0; // 위

int gameState = 0; // 게임 진행 상태
//gameState = 1 : 게임 시작
//gameState = 0 : 게임 오버
                  
unsigned long highScore = 0; // 최대 점수
unsigned long currentScore = 0; // 현재 점수

void setup() {

    Serial.begin(115200); //시리얼 통신 초기화. 보레이트 : 115200

    pinMode(X_INPUT, INPUT); // 아날로그 1번핀을 입력핀으로 설정
    pinMode(Y_INPUT, INPUT); // 아날로그 0번핀을 입력핀으로 설정

   lcd.init(); // LCD 초기화
   lcd.backlight(); // LCD backlight 킴

//   MsTimer2::set(10000,Level_Up); // 10초마다 Level_Up 함수 호출
//   MsTimer2::start();
}

void Level_Up(){
  if(gameState){ // 게임이 진행 중이라면 10초마다 레벨 1씩 증가
    if(level<20){
    level += 1;
    }
  }
  else { // 게임이 끝나면 레벨을 0으로 초기화
    level = 0;
  }
}

void High_Score(){ // 현재 점수와 비교하여 최고점수 반환
  if(currentScore >= highScore){
    highScore = currentScore;
  }
}

void Lcd() { 
  
    lcd.setCursor(0, 0);
    lcd.print("HighScore : "); // 최고 점수 표시
    lcd.print(highScore);
    
    if(gameState==1){ // 게임이 진행 중이라면 현재 레벨 표시
    lcd.setCursor(0, 1);
    lcd.print("score : ");
    lcd.print(currentScore);
    
    lcd.setCursor(11, 1);
    lcd.print("lv.");
    lcd.print(level);
    }
    else if(gameState==0){ // 게임이 끝나면 Game Over 표시
    lcd.setCursor(0, 1);
    lcd.print("Game Over");
    }
}

void loop() {
  //조이스틱 조작 시 시리얼 통신을 통해 게임기로 조작 명령을 보낸다.
    int yVal = analogRead(A0); // y축 기본 값은 512이며, y축 이동 범위는 0~1023이다.
    int xVal = analogRead(A1); // x축 기본 값은 512이며, 축 이동 범위 : 0~1023이다.
    
    if (xVal < 480) {
        if (joyStickFlagA == 0) { // 조작 플래그가 0일 때
            Serial.print("a"); // 왼쪽으로 이동
            joyStickFlagA = 1; // 조작 플래그를 통해 채터링 방지
        }
    } else {
        joyStickFlagA = 0; // 조작 플래그를 0으로 초기화
    }

    if (xVal > 540) {
        if (joyStickFlagD == 0) { // 조작 플래그가 0일 때
            Serial.print("d"); // 오른쪽으로 이동
            joyStickFlagD = 1; // 조작 플래그를 통해 채터링 방지
        }
    } else {
        joyStickFlagD = 0; // 조작 플래그를 0으로 초기화
    }

    if (yVal > 600) {
            Serial.print("s"); // 아래로 이동
    }

    if (yVal < 400) {
        if (joyStickFlagW == 0) { // 조작 플래그가 0일 때
            Serial.print("w"); // 블록을 시계 방향으로 90도 만큼 회전
            joyStickFlagW = 1; // 조작 플래그를 통해 채터링 방지
        }
    } else {
        joyStickFlagW = 0; // 조작 플래그를 0으로 초기화
    }
//  High_Score();
//  Lcd();
}

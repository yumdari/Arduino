// Segment_X - Arduino Pin // FND Pin
#define SEG_A 52 // 11
#define SEG_B 48 // 7
#define SEG_C 45 // 4
#define SEG_D 43 // 2
#define SEG_E 42 // 1
#define SEG_F 51 // 10
#define SEG_G 46 // 5

// FND_num - Arduino Pin // FND Pin
#define FND1 47  // 6
#define FND2 49 // 8
#define FND3 50 // 9
#define FND4 53 // 12

void seglight(byte number);
byte numbers[] = {
  B0111111,  // MSB   --  LSB
  B0000110,
  B1011011,
  B1001111,
  B1100110,
  B1101101,
  B1111101,
  B0000111,
  B1111111,
  B1101111
};

int FND[] = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G };
int FND_NO[] = {FND1, FND2, FND3, FND4};

void setup() {
  for (int i = 0 ; i < 7; i++) {
    pinMode(FND[i], OUTPUT);
  }
  for (int i = 0 ; i < 4; i++) {
    pinMode(FND_NO[i], OUTPUT);
    digitalWrite(FND_NO[i], HIGH);
  }
}

int ON = OUTPUT;
int intCnt = 0 ;

void loop() {

  if(intCnt < 10000) {
    intCnt++;
  } else {
    intCnt = 0;
  }
    
  unsigned long start = millis();
  for (unsigned long j = 0 ; j < 10 ; j = millis() - start) { // 600 밀리초 마다 실행

    // Dynamic 구동
    digitalWrite(FND1, LOW);                 // 1의 자리 켜기
    seglight(numbers[intCnt % 10]);
    delay(5);                                // 5ms 유지 후
    digitalWrite(FND1, HIGH);                // 끄기
    
    digitalWrite(FND2, LOW);                 // 10의 자리 켜기
    seglight(numbers[(intCnt / 10) % 10]);
    delay(5);                                // 5ms 유지 후
    digitalWrite(FND2, HIGH);                // 끄기
 
    digitalWrite(FND3, LOW);                 // 100의 자리 켜기
    seglight(numbers[(intCnt / 100) % 10]);
    delay(5);                                // 5ms 유지 후 
    digitalWrite(FND3, HIGH);                // 끄기

    digitalWrite(FND4, LOW);                 // 1000의 자리 켜기
    seglight(numbers[(intCnt / 1000) % 10]);
    delay(5);                                // 5ms 유지 후
    digitalWrite(FND4, HIGH);                // 끄기
  }
}

// Bit값으로 FND 각 LED 점등
void seglight(byte number) {
  for (int i = 0 ; i < 7 ; i++) {
    int bit = bitRead(number, i) ;
    digitalWrite(FND[i], bit);
  }
}

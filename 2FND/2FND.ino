int numArray[] = {
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
 //int numArray[10] = { 0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10 };
 //int numArray[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90 };
// 16진수를 사용해도 됨

const int segPins[] = {52, 48, 45, 43, 42, 51, 46, 44}; // Segment핀 번호
const int segNum = 2;                              // Segment 개수 (숫자 자리수)
const int vccPins[segNum] = { 50, 53 };            // 10, 11번 핀을 통해 seg#1, seg#2의 전원 인가

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(segPins[i], OUTPUT);                   // Segment핀 설정
  }
  for (int i = 0; i < segNum; i++) {
    pinMode(vccPins[i], OUTPUT);                   // seg#0, seg#1의 전원인가 핀 설정
  }
}

void loop() {
  for (int i = 0; i < 100; i++) {                  // 0~99까지 숫자를 표시
    for (int n = 0; n < 10; n++) {                 // 빠르게 카운트할 경우 모든 LED가 켜져 있는 것처럼 보여
      showNumber(i);                               // 숫자를 구분할 수 없으므로, 빠르게 10번씩 점멸시키면서 표시
    }
  }
}

void showNumber(int number) {
  if (number == 0) {
    showDigit(number, 0);                         // 0의 경우 (1의 자리수) Segment에만 0을 출력
  }
  else {
    for (int j = 0; j < segNum; j++) {            // 10의 자리, 1의 자리 출력을 위해 2번 실행
      if (number > 0) {                           // 출력값이 0보다 큰 경우에만 실행
        showDigit(number % 10, j);                // 1의 자리 숫자(%10)를 seg#0(j=0)에 출력 (if 10의 자리 숫자 = (number % 100) / 10))
        number = number / 10;                     // ※ 숫자를 10으로 나눠 10의 자리 숫자를 1의 자리 숫자로 만듦
      }                                           // if 처음에 주어진 숫자가 한 자리 수였으면,
      delay(5);                                   //    → 10으로 나눈 후에는 1의 자리값이 0이 되어, 0보다 큰 값이 안되므로 10의 자리 출력하지 않음
    }                                             // if 처음에 주어진 숫자가 두 자리 수였으면
  }                                               //    → 10으로 나눈 후 10의 자리 숫자가 1의 자리 수가 되므로, 10이 자리수를 seg#1(j=1)에 출력
}

void showDigit(int num, int digit) {              // num값과 digit(0→1의 자리수에 표시, 1→10의 자리수에 표시)을 넘겨받아
  int data = numArray[num];                       // num번째 배열값을 digit자리수에 표시할 data로 지정

  digitalWrite(vccPins[0], HIGH);                 // vcc핀에 전원 인가
  digitalWrite(vccPins[1], HIGH);                 // [0] = Arduino Pin10, [1] = Arduino Pin11

  for (int segLED = 0; segLED < 7; segLED++)      // 숫자 2진수의 7세그먼트 ON, OFF
  {
    if (data & 0x01) {                            // 1이면
      digitalWrite(segPins[segLED], HIGH);        // HIGH(끄고)
    }
    else {                                        // 1이 아니면(0이면)
      digitalWrite(segPins[segLED], LOW);         // LOW(끈다)
    }
    data >>= 1;                                   // data값을 1비트씩 오른쪽으로 쉬프트한 후
  }
  digitalWrite(vccPins[digit], LOW);              // 숫자 LED 한 자리 ON
}

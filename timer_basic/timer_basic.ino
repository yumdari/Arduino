#include <MsTimer2.h>

void flash() {
  static boolean output = HIGH;

  digitalWrite(26, output);
  output = !output;
}

void setup() {
  pinMode(26, OUTPUT);

  MsTimer2::set(500, flash); // flash함수를 500ms마다 호출한다
  MsTimer2::start();
}

void loop() {
}

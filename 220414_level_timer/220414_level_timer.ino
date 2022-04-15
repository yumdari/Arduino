#include <MsTimer2.h>
int level=0

void Level_Up(){
  level++;
}

void setup() {
  MsTimer2::set(30000, Level_Up); // 30초 주기
  MsTimer2::start();
}

void loop() {

}

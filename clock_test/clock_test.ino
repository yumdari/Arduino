#include <MsTimer2.h>

int h=0, m=0, s=0;

void setup()
{ 
  Serial.begin(9600);
  MsTimer2::set(1000, clocks);
  MsTimer2::start();
 
}

void loop(){
  
}
void clocks(){
  s++;
  if(s==60)
  {
    s=s%60;
    m++;
  }
  if(m==60)
  {
    m=m%60;
    h++;
  }
  Serial.println(s);
}

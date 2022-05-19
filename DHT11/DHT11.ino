#include <MsTimer2.h>
#include <DFRobot_DHT11.h>

DFRobot_DHT11 DHT;

#define DHT11_PIN 8

boolean sensor_read = 0;
char msg[15];

void setup() {
  Serial.begin(9600);
  MsTimer2::set(1000, test);
  MsTimer2::start();
}

void loop() {
  if(sensor_read) {
    char temp, humi;
    DHT.read(DHT11_PIN);
    temp = DHT.temperature;
    humi = DHT.humidity;
    sprintf(msg, "%d:%dL", humi, temp);
    Serial.write(msg);
  }
  sensor_read = 0;
}
void test() {
  sensor_read = !sensor_read;
}

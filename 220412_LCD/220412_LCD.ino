#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set LCD address to 0x27 for a 16 chars and 2 line display
//address : 0x3F, 0x27 
void setup() {
  lcd.init(); //LCD initiallize
  lcd.backlight(); // brightend the LCD backlight
}

void loop() {
  lcd.setCursor(0, 0); // move cursor
  lcd.printstr("start"); // lcd print
}

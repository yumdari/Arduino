 # include <Wire.h>
 # include <LiquidCrystal_I2C.h>

 # define CDS A3
 # define LED 10

int ledState = 0;
int cdsKey = 0;
int val = 0;

int arr[100] = {0};


LiquidCrystal_I2C lcd(0x27, 16, 2); // set LCD address to 0x27 for a 16 chars and 2 line display
//address : 0x3F, 0x27
void setup() {
    lcd.init(); //LCD initiallize
    lcd.backlight(); // brightend the LCD backlight

    pinMode(CDS, INPUT);

    pinMode(A0, INPUT);
    pinMode(LED, OUTPUT);

    Serial.begin(9600);

}

void Lcd() {
   
    lcd.setCursor(0, 0);
    lcd.print("val : ");
    lcd.print(val);
    if (val > 50) {
        lcd.print(" OFF");
    } else {
        lcd.print(" ON   ");
    }
}


void loop() {

    val = analogRead(A3);

    for(int idx = 0; idx<40 ; idx++){
       arr[idx] = val;
       Serial.println(arr[idx]);
    }
    if (arr[0] != arr[40]) {
       Lcd();
    }
}

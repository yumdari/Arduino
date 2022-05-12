
unsigned long curTimeMs = 0;
const int ledIntervalMs = 1000;

void setup() {
    // put your setup code here, to run once:
    DDRB = 0xff;
    Serial.begin(9600);
    curTimeMs = millis(); // current time milliseconds
}

void loop() {
    // put your main code here, to run repeatedly:
    int val = analogRead(A0);
   
    Serial.println(val);

    if (curTimeMs + ledIntervalMs < millis()) {
//        if (val > 100) {
              PORTB = 0xFF; //B00001000 = 0x0F = ledBlue
                                //B00010000 = 0x10 = ledGreen
                                //B0100000 = 0x20 = ledRed
            curTimeMs = millis();
//        }
    }
    if (curTimeMs + ledIntervalMs <  millis()) {
//        if (val > 100) {
 
            PORTB = 0x00; //B00001000 = ledBlue
            //B00010000 = ledGreen
            //B0100000 = ledRed
            curTimeMs = millis();
//        }
    }
}

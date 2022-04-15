#define MAX_LED_CNT 8
unsigned char LEDS[MAX_LED_CNT] = {26,27,28,29,30,31,32,33};

void responseLedState(unsigned char state)
{
    unsigned char i,led;
    String hex;
    //digitalRead가 안되는 경우가 있어서 state를 가지고 처리함.
    led = state;
    // led = 0x00;
    // for(i=0; i<MAX_LED_CNT; i++)
    // {
    //     if(digitalRead(LEDS[i]))
    //     {
    //         led |= 0x01 << i;
    //     }
    // }
    Serial.print("Arduino LED : ");
    hex = String((led>>1)&0x0F, HEX);
    hex += String(led&0x0F, HEX);
    Serial.println(hex);
}

void setup() 
{
    unsigned char i;
    Serial.begin(9600);
    for(i=0; i<MAX_LED_CNT; i++){
        pinMode(LEDS[i], OUTPUT);
    }
}

void loop() 
{
    unsigned char state = 0, i;
    state = Serial.read();

    if (state != 0xFF)
    {
        for(i=0; i<MAX_LED_CNT; i++)
        {
            if (state & (0x01 << i))
            {
                digitalWrite(LEDS[i], HIGH);
            }else{
                digitalWrite(LEDS[i], LOW);
            }
        }
        responseLedState(state);
    }
}

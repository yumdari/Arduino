int x_axis[] = {A0, 12, A2, 13, 5, A3, 7, 2};
int y_axis[] = {9, 8, 4, A1, 3, 10, 11, 6};

byte bigHeart[] = {
  B01100110,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000};

byte smallHeart[] = {
  B00000000,
  B00000000,
  B00010100,
  B00111110,
  B00111110,
  B00011100,
  B00001000,
  B00000000};
  
void setup(){
  for(int i=0;i<8;++i){
    pinMode(y_axis[i], OUTPUT);
    digitalWrite(y_axis[i], HIGH); 
    pinMode(x_axis[i], OUTPUT);
  }
}

void loop(){
  int pulseDelay = 800;

  show(smallHeart, 80);
  show(bigHeart, 160);
  delay(pulseDelay);
}

void show(byte * image, unsigned long duration){
  unsigned long start = millis();
  while(start+duration > millis()){
    for(int x=0;x<8;++x){
      digitalWrite(x_axis[x], HIGH);
      for(int y=0;y<8;++y){
        boolean pixel = bitRead(image[x], y);
        if(pixel==1){
          digitalWrite(y_axis[y],LOW);
        }
        delayMicroseconds(300);
        digitalWrite(y_axis[y], HIGH);
      }
      digitalWrite(x_axis[x],LOW);
    }
  }
}

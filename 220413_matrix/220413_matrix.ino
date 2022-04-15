int x_axis[] = {2,7,A3,5,13,A2,12,A0};


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

//byte l_block[] = {
//  B10000000,
//  B01000000,
//  B00100000,
//  B00010000,
//  B00001000,
//  B00000100,
//  B00000010,
//  B00000001, 
//};

byte l_block[] = {
  B11110000,
  B11110000,
  B11110000,
  B11110000,
  B11110000,
  B11110000,
  B11110000,
  B11110000,
};

  
void setup(){
  for(int i=0;i<8;++i){
     pinMode(x_axis[i],OUTPUT);  
    pinMode(y_axis[i],OUTPUT);
    digitalWrite(x_axis[i],LOW); //off
    digitalWrite(y_axis[i],HIGH); //off
  }
 
//  L_Block();
}

void I_Block(byte * image){
    int x, y;
    for(int x=0;x<8;x++){
    digitalWrite(x_axis[x], HIGH);
     boolean pixel = bitRead(image[x], x);
        if(pixel==1){
          digitalWrite(y_axis[x],LOW);
        }
        delay(50);
    }
      for(int y=0;y<=8;y++){
       
        digitalWrite(y_axis[y], HIGH);
        digitalWrite(x_axis[x],LOW);
        delay(50);
  }
}

void L_Block(){
  int x, y;
    int blockLength = 3;
    int blockHeight = 2;
        digitalWrite(x_axis[0], HIGH);
        digitalWrite(x_axis[1], HIGH);
        digitalWrite(x_axis[2], HIGH);
        for(y=7; y>0; y--){
        digitalWrite(y_axis[y],LOW); 
        delay(100);
        digitalWrite(y_axis[y],HIGH);
        delay(100);
        }
        digitalWrite(y_axis[0],LOW);
}

void loop(){
//  int pulseDelay = 800;
 I_Block(l_block);
//  show(l_block, 80);
//  show(bigHeart, 160);
//  delay(pulseDelay);
}

//void show(byte * image, unsigned long duration){
//  unsigned long start = millis();
//  while(start+duration > millis()){
//    for(int x=0;x<8;++x){
//      
//      for(int y=0;y<8;++y){
//        digitalWrite(x_axis[x], HIGH);
//        boolean pixel = bitRead(image[x], y);
//        if(pixel==1){
//          digitalWrite(y_axis[y],LOW);
//        }
//        delayMicroseconds(300);
//        digitalWrite(y_axis[y], HIGH);
//      }
//      digitalWrite(x_axis[x],LOW);
//    }
//  }
//}

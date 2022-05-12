int x_axis[] = {A0, 12, A2, 13, 5, A3, 7, 2};
int y_axis[] = {9, 8, 4, A1, 3, 10, 11, 6};
void setup() {
  for(int i=0; i<8; ++i){
   pinMode(x_axis[i],OUTPUT);
   pinMode(y_axis[i],OUTPUT);
    digitalWrite(x_axis[i],LOW); //off
    digitalWrite(y_axis[i],HIGH); //off
    }
}

void loop() {
  int x, y;
    for(int x=0;x<8;x++){
    digitalWrite(x_axis[x], HIGH);
          digitalWrite(y_axis[x],LOW);
        delay(500);
    }
      for(int y=0;y<=8;y++){
       
        digitalWrite(y_axis[y], HIGH);
        digitalWrite(x_axis[y],LOW);
        delay(500);
  }
}

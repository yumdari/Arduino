void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 
}
 
void loop() {
  // put your main code here, to run repeatedly:
  putString();
 
}
void putString() {
  Serial.println(" ** Method Start ** ");
  while (1) {
    if (Serial.available()) {
      String inString = Serial.readStringUntil('\n');
      Serial.println(inString);
      if (inString== "END") {
        Serial.println( " ** Method End ** ");
        break;
      }
    }
  }
}
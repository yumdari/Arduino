#define SW1 34
#define SW2 35

int i = 0;
int j = 0;
int sum = 50;
void setup() {
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(SW1) == HIGH) {
    i = 10;
  }
  else if (digitalRead(SW2) == HIGH) {
    j = -10;
  }
  manage();
}

void manage() {
  sum = sum + i + j;
  Serial.println(sum);
}

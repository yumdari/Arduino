#define FND_A 52
#define FND_B 48
#define FND_C 45
#define FND_D 43
#define FND_E 42
#define FND_F 51
#define FND_G 46
#define FND_DP 44
#define FND_D1 53
#define FND_D2 50
#define FND_D3 49
#define FND_D4 47

int t = 0;
int d2 = 11, d4 = 41;
int curTimeMs = 0;

int fndPort[12] = {FND_A, FND_B, FND_C, FND_D, FND_E, FND_F, FND_G, FND_DP, FND_D1, FND_D2, FND_D3, FND_D4};

int fndData[40][12] = {
  { 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0}, // 0 - d1
  { 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0}, // 1
  { 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0}, // 2
  { 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0}, // 3
  { 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0}, // 4
  { 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0}, // 5
  { 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0}, // 6
  { 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0}, // 7
  { 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0}, // 8
  { 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0}, // 9
  //{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0}, // 10 - Blank

  { 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1}, // 00 - d10
  { 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1}, // 10
  { 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1}, // 20
  { 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1}, // 30
  { 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1}, // 40
  { 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}, // 50
  { 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1}, // 60
  { 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1}, // 70
  { 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1}, // 80
  { 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1}, // 90
  //{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1}, // 20 - Blank

  { 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1}, // 0 - d100
  { 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1}, // 1
  { 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1}, // 2
  { 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1}, // 3
  { 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1}, // 4
  { 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1}, // 5
  { 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1}, // 6
  { 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1}, // 7
  { 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1}, // 8
  { 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1}, // 9
  //{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1}, // 10 - Blank

  { 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1}, // 0 - d1000
  { 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1}, // 1
  { 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1}, // 2
  { 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1}, // 3
  { 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1}, // 4
  { 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1}, // 5
  { 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1}, // 6
  { 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1}, // 7
  { 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1}, // 8
  { 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1}, // 9
  //{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1}, // 10 - Blank
};

void setup() {
  Serial.begin(9600);
  for (int i = 0 ; i < 41 ; i++)
  {
    pinMode(fndPort[i], OUTPUT);
  }
  curTimeMs = millis();
}

void loop() {
  if (curTimeMs + 1000 < millis()) {
    t++;
    Serial.println(t);
    curTimeMs = millis();
  }

  for (int i = 0 ; i < 12 ; i++) {
    digitalWrite(fndPort[i], fndData[t][i]);
    if (t == 10)
      t = 0;
    d2++;
    if (d2 == 20)
      d2 = 0;

        //for (int i = 0 ; j < 12 ; j++) {
            digitalWrite(fndPort[d2], fndData[d2][d2]);
  }

  //delay(1000);
}

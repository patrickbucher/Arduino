const int a = 220;
const int b = 233;
const int h = 245;
const int c = 262;

const int notes[] = {a, b, h, c};

void setup() {
  Serial.begin(9600);
}

void loop() {
  int keyVal = analogRead(A0);
  Serial.println(keyVal);
  switch (keyVal) {
    case 1023:
      tone(8, a);
      break;
    case 1002:
      tone(8, b);
      break;
    case 511:
      tone(8, h);
      break;
    case 8:
      tone(8, c);
      break;
    default:
      noTone(8);
      break;
  }
}

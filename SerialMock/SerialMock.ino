const byte buttonPin = 2;
const byte ledPinB = 10;
const byte ledPinG = 11;
const byte ledPinY = 12;
const byte ledPinR = 13;

void pushed();
void exclusiveOn(byte);

void setup() {
  Serial.begin(9600);
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), pushed, RISING);
}

void loop() {
  // TODO: read commands such as S157;
  if (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == 'G') {
      exclusiveOn(ledPinB);
    } else if (c == 'S') {
      exclusiveOn(ledPinY);
    } else if (c == 'D') {
      exclusiveOn(ledPinG);
    } else {
      exclusiveOn(ledPinR);
    }
  }
}

void pushed() {
  Serial.write('L');
  Serial.flush();
}

void exclusiveOn(byte pin) {
  for (int i = 10; i <= 13; i++) {
    digitalWrite(i, i == pin ? HIGH : LOW);
  }
}

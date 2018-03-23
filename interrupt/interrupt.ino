const byte ledPinGreen = 11;
const byte ledPinYellow = 12;
const byte ledPinRed = 13;

const byte interruptPin = 2;

volatile byte state = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), pushed, HIGH);
}

void loop() {
  if (state) {
    digitalWrite(ledPinGreen, LOW);
    digitalWrite(ledPinRed, HIGH);
    delay(100);
    digitalWrite(ledPinRed, LOW);
    digitalWrite(ledPinYellow, HIGH);
    delay(100);
    digitalWrite(ledPinYellow, LOW);
    digitalWrite(ledPinGreen, HIGH);
    delay(100);
  } else {
    digitalWrite(ledPinGreen, LOW);
    digitalWrite(ledPinYellow, LOW);
    digitalWrite(ledPinRed, LOW);
  }
}

void pushed() {
  state = LOW;
  Serial.write("pong;");
}

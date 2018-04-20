const byte buttonPin = 2;
const byte ledPinB = 10;
const byte ledPinG = 11;
const byte ledPinY = 12;
const byte ledPinR = 13;

#define BUF_LEN 1024
byte buf[BUF_LEN];
int n;

void pushed();
void exclusiveOn(byte);
void clear_buf();
int extract_number_from_buf();
void blink(int, int);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(100);
  }

  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), pushed, RISING);

  n = 0;
  clear_buf();
}

void loop() {
  if (Serial.available() > 0) {
    byte b = Serial.read();
    char c = (char)b;
    Serial.write(c);
    if (c == 'G') {
      clear_buf();
      exclusiveOn(ledPinB);
    } else if (c == 'H') {
      clear_buf();
      exclusiveOn(ledPinY);
    } else if (c == 'D') {
      clear_buf();
      exclusiveOn(ledPinG);
    } else if (c == 'S' || (buf[0] == (byte)'S' && c >= '0' && c <= '9')) {
      if (n < BUF_LEN - 1) {
        buf[n++] = (byte)c;
      } else {
        clear_buf();
      }
    } else if (buf[0] == 'S' && c == ';') {
      char str[100];
      int duration = extract_number_from_buf();
      blink(duration, ledPinR);
      clear_buf();
    }
  }
}

void blink(int ms, int pin) {
  digitalWrite(pin, HIGH);
  delay(ms);
  digitalWrite(pin, LOW);
}

int extract_number_from_buf() {
  int number = 0;
  for (int i = 1; i < n && buf[i] != '\0'; i++) {
    if (buf[i] >= '0' && buf[i] <= '9') {
      number = number * 10 + (buf[i] - '0');
    } else {
      break;
    }
  }
  return number;
}

void clear_buf() {
  n = 0;
  for (int i = 0; i < BUF_LEN; i++) {
    buf[i] = '\0';
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

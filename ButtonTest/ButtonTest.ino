const int waitMillis = 1;

const int button = 2;

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);
}

void loop() {
  delay(1000);
  Serial.print("waiting...\n");
  while (digitalRead(button) == LOW);
  Serial.print("button pressed\n");
  int millisPressed = 0;
  while (digitalRead(button) == HIGH) {
    delay(waitMillis);
    millisPressed += waitMillis;
  }
  Serial.print("button finally released, was pressed for ");
  Serial.print(millisPressed);
  Serial.print(" milliseconds\n");
}

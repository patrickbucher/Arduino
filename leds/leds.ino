const int led_red = 11;
const int led_yellow = 12;
const int led_green = 13;

void setup() {
  pinMode(led_red, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_green, OUTPUT);

  digitalWrite(led_red, LOW);
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_green, LOW);
}

void loop() {
  digitalWrite(led_red, LOW);
  digitalWrite(led_green, HIGH);
  delay(2000);
  digitalWrite(led_green, LOW);
  digitalWrite(led_yellow, HIGH);
  delay(1000);
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_red, HIGH);
  delay(5000);
}

#include <LiquidCrystal.h>

const int red_led = 9;
const int green_led = 10;
const int button = 1;
const int empty_pin = A4;

struct result {
  int duration;
  struct result *slower;
}

struct result *first = null;

int fastest = 999999;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(button, INPUT);
  int seed = analogRead(empty_pin);
  randomSeed(seed);
}

void push(int pin) {
  while (digitalRead(pin) == LOW);
  while (digitalRead(pin) == HIGH);
}

int randomInt(int min, int max) {
  return random() % (max - min + 1) + min;
}

void loop() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(red_led, HIGH);
    digitalWrite(green_led, HIGH);
    delay(150);
    digitalWrite(red_led, LOW);
    digitalWrite(green_led, LOW);
    delay(150);
  }
  lcd.clear();
  lcd.print("Reaction Test");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Push Button");
  push(button);
  digitalWrite(red_led, HIGH);
  int wait = randomInt(1000, 2000);
  delay(wait);
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, HIGH);
  unsigned long start = millis();
  push(button);
  unsigned long done = millis();
  int reaction_time = done - start;
  lcd.clear();
  lcd.print("Reaction Time:");
  lcd.setCursor(0, 1);
  lcd.print(reaction_time);
  lcd.print(" ms.");
  if (reaction_time < fastest) {
    fastest = reaction_time;
    lcd.print(" #1");
  }
  delay(1000);
}

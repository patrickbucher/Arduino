#include <LiquidCrystal.h>

const int red_led = 9;
const int green_led = 10;
const int button = 1;
const int empty_pin = A4;

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

struct result {
  short reaction_time;
  struct result *prev;
  struct result *next;
};

struct result *first = NULL;

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
  short reaction_time = done - start;
  lcd.clear();
  lcd.print("Reaction Time:");
  lcd.setCursor(0, 1);
  lcd.print(reaction_time);
  lcd.print(" ms.");

  struct result *new_result = (result*)malloc(sizeof(struct result));
  if (new_result == NULL) {
    lcd.print("memory full");
    exit(1);
  }
  new_result->reaction_time = reaction_time;
  new_result->prev = NULL;
  new_result->next = NULL;
  byte rank = 1;
  if (first == NULL) {
    first = new_result;
  } else {
    struct result *tmp = first;
    do {
      if (new_result->reaction_time < tmp->reaction_time) {
        new_result->next = tmp;
        new_result->prev = tmp->prev;
        if (tmp->prev != NULL) {
          tmp->prev->next = new_result;
        }
        tmp->prev = new_result;
        break;
      } else {
        rank++;
        tmp = tmp->next;
      }
    } while (tmp != NULL);
    if (tmp == first) {
      first = new_result;
    }
  }
  lcd.print(" #");
  lcd.print(rank);
  delay(1000);
}

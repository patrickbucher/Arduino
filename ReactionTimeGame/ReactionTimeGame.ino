#include <LiquidCrystal.h>

const int red_led = 9;
const int green_led = 10;
const int button = 1;
const int empty_pin = A4;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  int seed;

  lcd.begin(16, 2);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(button, INPUT);
  seed = analogRead(empty_pin);
  randomSeed(seed);
}

void push(int pin) {
  // wait until button was pushed down...
  while (digitalRead(pin) == LOW);
  // ... and released again
  while (digitalRead(pin) == HIGH);
}

int randomInt(int min, int max) {
  return random() % (max - min + 1) + min;
}

struct result {
  short reaction_time;
  struct result *next;
};

struct result *first = NULL;

byte rank_result(int reaction_time) {
  struct result *new_result, *tmp, *last;
  byte rank;
  bool attached;

  new_result = (result*)malloc(sizeof(struct result));
  if (new_result == NULL) {
    exit(1);
  }
  new_result->reaction_time = reaction_time;
  new_result->next = NULL;

  rank = 1;
  attached = false;
  if (first == NULL) {
    // nothing there yet
    first = new_result;
  } else {
    tmp = first;
    last = NULL;
    do {
      if (new_result->reaction_time < tmp->reaction_time) {
        // attach new result in front of next slower entry
        new_result->next = tmp;
        if (last != NULL) {
          last->next = new_result;
        }
        attached = true;
        break;
      } else {
        rank++;
        last = tmp;
        tmp = tmp->next;
      }
    } while (tmp != NULL);
    if (tmp == first && tmp != NULL && first != NULL) {
      // new_result was inserted before tmp, would be NULL otherwise
      first = new_result;
    } else if (!attached) {
      // no entry found to add new one in front of it, attach at the end
      last->next = new_result;
    }
  }
  return rank;
}

void loop() {
  unsigned int i, wait;
  unsigned long start, done;
  unsigned short reaction_time;
  byte rank;

  // optical start signal
  for (i = 0; i < 3; i++) {
    digitalWrite(red_led, HIGH);
    digitalWrite(green_led, HIGH);
    delay(150);
    digitalWrite(red_led, LOW);
    digitalWrite(green_led, LOW);
    delay(150);
  }
  lcd.clear();

  // make user initialize the game
  lcd.print("Reaction Test");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Push Button");
  push(button);

  // the actual game
  digitalWrite(red_led, HIGH);
  wait = randomInt(1000, 2000);
  delay(wait); // TODO: implement non-blocking wait to detect false starts
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, HIGH);
  start = millis();
  push(button);
  done = millis();
  reaction_time = done - start;
  lcd.clear();

  // output result
  lcd.print("Reaction Time:");
  lcd.setCursor(0, 1);
  lcd.print(reaction_time);
  lcd.print(" ms.");
  rank = rank_result(reaction_time);
  lcd.print(" #");
  lcd.print(rank);

  delay(1000);
}

#include <LiquidCrystal.h>

// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int switchPin = 6;
const int potPin = A0;

const int redLed = 9;
const int greenLed = 10;

const int button = 8;

void setup() {
  //  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(button, INPUT);
  for (int i = 0; i < 3; i++) {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, HIGH);
    delay(100);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    delay(100);
  }
}

int buttonState = 0;
int previousButtonState = 0;
int red = 0;

void loop() {
  buttonState = digitalRead(button);
  Serial.print(HIGH == buttonState);
  Serial.print('\n');
  if (buttonState != previousButtonState) {
    if (red == 0) {
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);
      red = 1;
    } else {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
      red = 0;
    }
    previousButtonState = buttonState;
  }
}

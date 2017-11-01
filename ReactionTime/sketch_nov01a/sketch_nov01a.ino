#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  
  lcd.begin(16, 2);
  pinMode(switchPin.INPUT);
  lcd.print("Hello World");
  lcd.setCursor(0, 1);
  lcd.print("Wie gayts?");
}

void loop() {

}

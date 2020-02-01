#include <Wire.h>
#include <LiquidCrystal.h>

#include "SparkFun_SCD30_Arduino_Library.h" 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SCD30 airSensor;

int reply;

void setup()
{
    Wire.begin();
    lcd.begin(16, 2);
    lcd.print("Carbon Dioxide");
    lcd.setCursor(0, 1);

    Serial.begin(9600);
    Serial.println("SCD30 Example");

    airSensor.begin(); //This will cause readings to occur every two seconds
}

void loop()
{
    int co2;
    char co2str[10];
    lcd.clear();
    if (airSensor.dataAvailable())
    {
        lcd.print("Carbon Dioxide");
        lcd.setCursor(0, 1);
        co2 = airSensor.getCO2();
        sprintf(co2str, "%d ppm", co2);
        lcd.print(co2str);

        Serial.print("co2(ppm):");
        Serial.print(co2);
        Serial.println();
    }
    else {
        lcd.print("No data");
        Serial.println("No data");
    }
    delay(5000);
}

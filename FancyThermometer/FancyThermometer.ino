const int temperatureIn = A0;
const int minOut = 6;
const int maxOut = 13;
const int nLeds = maxOut - minOut + 1;

const float voltage = 5.0;
const float maxSensor = 1024.0;

float initialTemperature;

void setup() {
  Serial.begin(9600);
  for (int pin = minOut; pin <= maxOut; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  initialTemperature = getCurrentTemperature();
}

float getCurrentTemperature() {
  int sensorValue = analogRead(temperatureIn);
  float voltageValue = (sensorValue / maxSensor) * voltage;
  float temperature = (voltageValue - 0.5) * 100;
  return temperature;  
}

void activateLeds(int uppermost) {
  for (int i = minOut; i <= maxOut; i++) {
    digitalWrite(i, i < uppermost + minOut ? HIGH : LOW);
  }
}

void loop() {
  float temperature = getCurrentTemperature();
  Serial.println(temperature);
  int maxLed = (temperature - initialTemperature) / 0.5 + (nLeds / 2);
  Serial.println(maxLed);
  activateLeds(maxLed);
  delay(1000);
}

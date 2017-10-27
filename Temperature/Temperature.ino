const int sensorPin = A0;

void setup() {
  Serial.begin(9600);
  for (int pinNumber = 2; pinNumber <= 5; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
  }
}

void loop() {
  int sensorVal = analogRead(sensorPin);
  float voltage = (sensorVal / 1024.0) * 5.0;
  float temperature = (voltage - 0.5) * 100;
  
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);
  Serial.print(", Volts: ");
  Serial.print(voltage);
  Serial.print(", Temperature: ");
  Serial.print(temperature);
  Serial.print("\n");

  if (temperature < 20) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(4, LOW);
  } else if (temperature >= 20 && temperature < 22) {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  } else if (temperature >= 22 && temperature < 24) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  } else if (temperature > 24) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }
  delay(500);
}

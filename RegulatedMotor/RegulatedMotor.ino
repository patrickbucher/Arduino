const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchPin = 5;
const int potPin = A0;

int onOff = 0;
int previousOnOff = 0;
int direction = 0;
int previousDirection = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;

void setup() {
  Serial.begin(9600);
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW);
}

void loop() {
  delay(10);
  onOff = digitalRead(onOffSwitchPin);
  direction = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin) / 4;
  
  if (onOff != previousOnOff) {
    if (onOff == HIGH) {
      motorEnabled = motorEnabled == 1 ? 0 : 1;
      if (motorEnabled) {
        Serial.println("Motor On");
      } else {
        Serial.println("Motor Off");
      }
    }
  }

  if (direction != previousDirection) {
    Serial.println("Switch Direction");
    if (direction == HIGH) {
      motorDirection = motorDirection == 1 ? 0 : 1;
    }
  }

  if (motorDirection == 1) {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  } else {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);    
  }

  if (motorEnabled == 1) {
    analogWrite(enablePin, motorSpeed);
    Serial.print("Speed: ");
    Serial.print(motorSpeed);
    Serial.print('\n');
  } else {
    analogWrite(enablePin, 0);
  }
  previousDirection = direction;
  previousOnOff = onOff;
}

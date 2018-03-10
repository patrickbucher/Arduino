#define MSG_LEN 1024

const int led_blue = 10;
const int led_red = 11;
const int led_yellow = 12;
const int led_green = 13;

byte incoming;
char message[MSG_LEN];
int n;

void setup() {
  pinMode(led_blue, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_green, OUTPUT);

  Serial.begin(9600);

  n = 0;
}

void loop() {
  while (Serial.available() > 0) {
    incoming = Serial.read();
    Serial.print((char)incoming);
    if (incoming == (byte)';' || n == MSG_LEN - 1) {
      message[n++] = '\0';
      Serial.print('\r');
      Serial.print('\n');
      handle(message, n - 1);
      n = 0;
      break;
    } else {
      message[n++] = (char)incoming;
    }
  }
}

void handle(char *command, int n) {
  if (strncmp("red_on", command, n) == 0) {
    digitalWrite(led_red, HIGH);
  } else if (strncmp("red_off", command, n) == 0) {
    digitalWrite(led_red, LOW);
  } else if (strncmp("yellow_on", command, n) == 0) {
    digitalWrite(led_yellow, HIGH);
  }  else if (strncmp("yellow_off", command, n) == 0) {
    digitalWrite(led_yellow, LOW);
  } else if (strncmp("green_on", command, n) == 0) {
    digitalWrite(led_green, HIGH);
  }  else if (strncmp("green_off", command, n) == 0) {
    digitalWrite(led_green, LOW);
  } else if (strncmp("blue_on", command, n) == 0) {
    digitalWrite(led_blue, HIGH);
  }  else if (strncmp("blue_off", command, n) == 0) {
    digitalWrite(led_blue, LOW);
  } else {
    Serial.print("unknown command: ");
    Serial.println(command);
  }
}


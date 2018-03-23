char buf[1024];
int n;

void setup() {
  Serial.begin(9600);
  n = 0;
}

void loop() {
  while (Serial.available() > 0) {
    byte incoming = Serial.read();
    char c = (char)incoming;
    Serial.print(c);
    buf[n++] = c;
    if (c == ';') {
      buf[n++] = '\0';
      Serial.print('\n');
      char *cmd = (char*)malloc(sizeof(char) * n);
      strncpy(cmd, buf, n);
      execute(cmd);
      n = 0;
    }
  }
}

void execute(char *cmd) {
  Serial.println(cmd);
}


String buffer = "";
unsigned long lastreceived = 0;
long data;
void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (millis() - lastreceived > 1000) {
    while (Serial1.available()) {
      Serial1.read();
    }
    while (1) {
      if (Serial1.available()) {
        if (char(Serial1.peek()) == char(13)) {
          break;
        }
        else {
          buffer = buffer + char(Serial1.read());
          Serial.println(buffer);
        }
      }
    }
    Serial.println(buffer);
    data = buffer.toInt();
    buffer = "";
    Serial.println(data);
    lastreceived = millis();
  }
}

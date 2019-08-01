String buffer = "";
unsigned long lastreceived = 0;
long data;
const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
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
        }
      }
    }
    //     Serial.println(buffer);
    data = buffer.toInt();
    buffer = "";
    //    Serial.println(data);
    total = total - readings[readIndex];
    readings[readIndex] = data;
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;
    // calculate the average:
    average = total / numReadings;
    // if we're at the end of the array...
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
    }
    Serial.println(average);
    lastreceived = millis();
  }
}

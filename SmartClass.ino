#include "Callendar.h"
Callendar callendar;

void inSerial();

void setup() {
  // put your setup code here, to run once:
  callendar.begin(9600, false);
  Serial.begin(9600);
  Serial.println("Testing...");
  callendar.add("15:00:00", "16:30:00", inSerial);
}

void loop() {
  // put your main code here, to run repeatedly:
  callendar.loop();
  delay(5000);
}

void inSerial() {
  Serial.println("Dang trong ke hoach...");
}

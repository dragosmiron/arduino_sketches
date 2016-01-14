//This sketch detects a change of more than 10 cm and light an LED

#include <NewPing.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200
#define OUTPUT_PIN 9
#define DELTA 10
float value = 1000;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(115200);
  pinMode(OUTPUT_PIN, OUTPUT);
}

void loop() {
  delay(50);
  int uS = sonar.ping_cm();
  if (uS > (value + DELTA) || (uS < value-10)){
    value = uS;
    Serial.print("Ping: ");
    Serial.print(uS);
    Serial.println("cm");
    digitalWrite(OUTPUT_PIN, HIGH);
    delay(2000);
    digitalWrite(OUTPUT_PIN, LOW);
  }

}

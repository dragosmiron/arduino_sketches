const int ledPin = 8;     
const int knockSensor = A0;
const int threshold = 200; 

int sensorReading = 0; 
int ledState = LOW;   

void setup() {
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  sensorReading = analogRead(knockSensor);
  //Serial.println(sensorReading);
  if (sensorReading <= threshold) {
    // toggle the status of  ledPin
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    Serial.println("Clap!");
    delay(1000);
  }
}


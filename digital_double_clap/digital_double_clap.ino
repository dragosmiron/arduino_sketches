/*
  This sketch reads a piezo element to see if a sound is made (eg. clap)
  two times in succession after which an action is performed.
  The code listens for a double clap in a 1.5 second period, after which
  the whole system gets reset

  For this sketch, the sensor sensitivity is adjusted manually on the board itself.
  For more granular difference, consider switching to digitalRead to analogRead
*/

const bool DEBUG = true; //allow serial prints

const int ledPin = 8;     
const int soundSensor = A0;
const int threshold = 200; 
//these two delays below are required because echo can still trigger the sensor
const int delayBetweenClaps = 300;
const int delatForReset = 300;
const int resetPeriod = 1500; //milliseconds

int sensorReading = 1; 
int ledState = LOW; 
unsigned long timeOfClap = 0;

enum State {waiting, first_clap, waiting_2nd_clap};
State current_state = waiting;

void setup() {
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  sensorReading = digitalRead(soundSensor);
  
  if (sensorReading == LOW) {
    if (current_state == State::waiting){
      current_state = State::first_clap;
      timeOfClap = millis();
      debugSerialPrintln("State = first clap");
    }
    if (current_state == State::waiting_2nd_clap){
      performAction();
      
      current_state = State::waiting;
      debugSerialPrintln("State = waiting");
      delay(delayBetweenClaps); // delay after which the process resumes
    }
  } else {
    if (current_state == State::first_clap) {
      current_state = State::waiting_2nd_clap;
      debugSerialPrintln("State = waiting_2nd_clap");
      delay(300);// delay after which is listening for second clap
    }
  }
  if (timeOfClap > 0 && timeFromClap() % resetPeriod == 0 && current_state == State::waiting_2nd_clap){
    current_state = State::waiting;
    timeOfClap = 0;
    debugSerialPrintln("Too long for 2nd clap, resetting..");
  }
}

void performAction(){
  // toggle the status of  ledPin
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
  debugSerialPrintln("2xClap!");
}

unsigned long timeFromClap(){
  return millis()-timeOfClap;
}

void debugSerialPrintln(String text){
  if (DEBUG) {
    Serial.println(text);
  }
}


const bool DEBUG = true;

const int ledPin = 8;     
const int knockSensor = A0;
const int threshold = 200; 
const int resetPeriod = 1500; //milliseconds


int sensorReading = 1; 
int ledState = LOW; 
int state = 0;  
unsigned long timeOfClap = 0;

enum State {waiting, first_clap, waiting_2nd_clap};
State current_state = waiting;

void setup() {
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  sensorReading = digitalRead(knockSensor);
  
  if (sensorReading == LOW) {
    if (current_state == State::waiting){
      current_state = State::first_clap;
      timeOfClap = millis();
      debugSerialPrintln("State = first clap");
    }
    if (current_state == State::waiting_2nd_clap){
      // toggle the status of  ledPin
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
      debugSerialPrintln("2xClap!");
      current_state = State::waiting;
      debugSerialPrintln("State = waiting");
      delay(300); // delay after which the process resumes
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

unsigned long timeFromClap(){
  return millis()-timeOfClap;
}

void debugSerialPrintln(String text){
  if (DEBUG) {
    Serial.println(text);
  }
}


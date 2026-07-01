/**
 * @file traffic_light.ino
 * @author Gauransh Pundir
 * @date 2026-07-01
 * @description Module 2 Q14 - Non-blocking Traffic Light Controller with high-priority
 * pedestrian override interrupt monitoring and real-time state telemetry.
 */

const int RED_LED = 11;
const int YELLOW_LED = 10;
const int GREEN_LED = 9;
const int PEDESTRIAN_BUTTON = 7;

enum TrafficState { STATE_RED, STATE_YELLOW, STATE_GREEN, STATE_PEDESTRIAN_OVERRIDE };
TrafficState currentState = STATE_RED;

unsigned long stateStartTime = 0;
const unsigned long RED_DURATION = 5000;
const unsigned long YELLOW_DURATION = 2000;
const unsigned long GREEN_DURATION = 4000;
const unsigned long PEDESTRIAN_DURATION = 8000;

volatile bool pedestrianRequested = false;

void pedestrianISR() {
  pedestrianRequested = true;
}

void logState(String stateName) {
  Serial.print("[Timestamp: ");
  Serial.print(millis());
  Serial.print(" ms] Traffic State Transition -> ");
  Serial.println(stateName);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  pinMode(PEDESTRIAN_BUTTON, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(PEDESTRIAN_BUTTON), pedestrianISR, FALLING);
  
  stateStartTime = millis();
  logState("RED (Initial Loop)");
}

void loop() {
  unsigned long currentMillis = millis();

  if (pedestrianRequested && currentState != STATE_PEDESTRIAN_OVERRIDE) {
    pedestrianRequested = false; 
    currentState = STATE_PEDESTRIAN_OVERRIDE;
    stateStartTime = currentMillis;
    logState("PEDESTRIAN OVERRIDE ACTIVATED");
  }

  switch (currentState) {
    case STATE_RED:
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);

      if (currentMillis - stateStartTime >= RED_DURATION) {
        currentState = STATE_YELLOW;
        stateStartTime = currentMillis;
        logState("YELLOW");
      }
      break;

    case STATE_YELLOW:
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);

      if (currentMillis - stateStartTime >= YELLOW_DURATION) {
        currentState = STATE_GREEN;
        stateStartTime = currentMillis;
        logState("GREEN");
      }
      break;

    case STATE_GREEN:
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);

      if (currentMillis - stateStartTime >= GREEN_DURATION) {
        currentState = STATE_RED;
        stateStartTime = currentMillis;
        logState("RED");
      }
      break;

    case STATE_PEDESTRIAN_OVERRIDE:
      digitalWrite(RED_LED, HIGH); 
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);

      if (currentMillis - stateStartTime >= PEDESTRIAN_DURATION) {
        pedestrianRequested = false; 
        currentState = STATE_YELLOW; 
        stateStartTime = currentMillis;
        logState("RESET FROM OVERRIDE -> CLEARING YELLOW");
      }
      break;
  }
}
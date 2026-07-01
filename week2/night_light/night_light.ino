const int PWM_LED = 6;
const int MODE_BUTTON = 2;

enum LightMode { MODE_SLOW_BREATHE, MODE_FAST_PULSE, MODE_SOS };
volatile LightMode operationalMode = MODE_SLOW_BREATHE;
volatile bool modeChangedFlag = true;

const int SOS_DOT = 200;
const int SOS_DASH = 600;

void modeChangeISR() {
  if (operationalMode == MODE_SLOW_BREATHE) {
    operationalMode = MODE_FAST_PULSE;
  } else if (operationalMode == MODE_FAST_PULSE) {
    operationalMode = MODE_SOS;
  } else {
    operationalMode = MODE_SLOW_BREATHE;
  }
  modeChangedFlag = true;
}

void setup() {
  Serial.begin(9600);
  pinMode(PWM_LED, OUTPUT);
  pinMode(MODE_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(MODE_BUTTON), modeChangeISR, FALLING);
}

void executeBreatheCycle(int fadeInterval) {
  for (int b = 0; b <= 255; b++) {
    if (modeChangedFlag) return;
    analogWrite(PWM_LED, b);
    delay(fadeInterval);
  }
  for (int b = 255; b >= 0; b--) {
    if (modeChangedFlag) return;
    analogWrite(PWM_LED, b);
    delay(fadeInterval);
  }
}

void triggerSosSymbol(int activeDuration) {
  if (modeChangedFlag) return;
  digitalWrite(PWM_LED, HIGH);
  delay(activeDuration);
  digitalWrite(PWM_LED, LOW);
  delay(200);
}

void loop() {
  if (modeChangedFlag) {
    modeChangedFlag = false;
    Serial.print("MODE CHANGE: ");
    if (operationalMode == MODE_SLOW_BREATHE) Serial.println("Slow Breathing");
    else if (operationalMode == MODE_FAST_PULSE) Serial.println("Fast Pulse");
    else Serial.println("SOS Pattern");
  }

  switch (operationalMode) {
    case MODE_SLOW_BREATHE:
      executeBreatheCycle(6);
      break;

    case MODE_FAST_PULSE:
      executeBreatheCycle(1);
      break;

    case MODE_SOS:
      for(int i = 0; i < 3; i++) triggerSosSymbol(SOS_DOT);
      delay(400);
      for(int i = 0; i < 3; i++) triggerSosSymbol(SOS_DASH);
      delay(400);
      for(int i = 0; i < 3; i++) triggerSosSymbol(SOS_DOT);
      delay(1500);
      break;
  }
}
const int SYSTEM_LED = 13;
int mainBlinkCounter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SYSTEM_LED, OUTPUT);
  digitalWrite(SYSTEM_LED, LOW);
  Serial.println("=== SERIAL TERMINAL SUBSYSTEM ONLINE ===");
}

void loop() {
  if (Serial.available() > 0) {
    String inputBuffer = Serial.readStringUntil('\n');
    inputBuffer.trim();

    if (inputBuffer == "LED_ON") {
      digitalWrite(SYSTEM_LED, HIGH);
      Serial.println("SUCCESS: LED activated.");
    } 
    else if (inputBuffer == "LED_OFF") {
      digitalWrite(SYSTEM_LED, LOW);
      Serial.println("SUCCESS: LED deactivated.");
    } 
    else if (inputBuffer.startsWith("BLINK_")) {
      String countValueStr = inputBuffer.substring(6);
      int pulseTarget = countValueStr.toInt();

      if (pulseTarget >= 1 && pulseTarget <= 9) {
        for (int i = 0; i < pulseTarget; i++) {
          digitalWrite(SYSTEM_LED, HIGH);
          delay(250);
          digitalWrite(SYSTEM_LED, LOW);
          delay(250);
          mainBlinkCounter++;
        }
        Serial.print("SUCCESS: Blink sequence complete. Total counts: ");
        Serial.println(pulseTarget);
      } else {
        Serial.println("ERROR: Unknown command");
      }
    } 
    else if (inputBuffer == "STATUS") {
      Serial.print("LED State: ");
      Serial.print(digitalRead(SYSTEM_LED));
      Serial.print(" | Total Blinks: ");
      Serial.println(mainBlinkCounter);
    } 
    else if (inputBuffer == "RESET") {
      mainBlinkCounter = 0;
      Serial.println("SUCCESS: Blink counter reset to zero.");
    } 
    else {
      Serial.println("ERROR: Unknown command");
    }
  }
}
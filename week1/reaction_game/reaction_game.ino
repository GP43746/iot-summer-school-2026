/**
 * @file reaction_game.ino
 * @author Gauransh Pundir
 * @date 2026-06-28
 * @description Week 1 Q4 - Digital reaction reflex tester utilizing high-resolution 
 * time differential calculation metrics via millis() and hardware pull-up tracking.
 */

const int ledPins[] = {11, 10}; // Unpredictable filler sequence LEDs (Red, Yellow)
const int targetLED = 9;        // The Green action trigger signal LED
const int buttonPin = 2;        // Push button input tracking pin (Interrupt/Digital input)

void setup() {
  Serial.begin(9600);
  
  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);
  pinMode(targetLED, OUTPUT);
  
  // Initialize with internal pull-up network: Button press reads LOW
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Seed the random number generator using floating ambient analog noise
  randomSeed(analogRead(A5));
  
  Serial.println("=== DIGITAL REACTION GAME INITIALIZED ===");
  Serial.println("Instructions: Await the Green LED signal, then press the trigger button immediately!");
}

void loop() {
  Serial.println("\nStarting random generation loop... Keep your hand off the trigger!");
  digitalWrite(targetLED, LOW);
  
  // 1. Generate an unpredictable random LED flashing waiting period sequence
  int randomBlinks = random(4, 9); // Run between 4 to 8 preparatory blinks
  for (int i = 0; i < randomBlinks; i++) {
    int selectedLED = ledPins[random(0, 2)]; // Randomly choose Red or Yellow
    int holdTime = random(200, 700);        // Random active interval duration
    
    digitalWrite(selectedLED, HIGH);
    delay(holdTime);
    digitalWrite(selectedLED, LOW);
    delay(random(150, 400));                // Random quiet buffer space
  }
  
  // Add a final dead-time safety rest phase (1 to 3 seconds) before the signal
  delay(random(1000, 3000));
  
  // Cheat detection safeguard check: Is user already holding down the button down early?
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("FAUL / CHEAT DETECTED: Do not hold down the trigger button early!");
    delay(3000); // Penalty delay window
    return;      // Reset the main loop cycle execution
  }
  
  // 2. Fire the Green Action LED and record the start time stamp
  digitalWrite(targetLED, HIGH);
  unsigned long signalTriggeredTime = millis();
  
  // 3. Block execution until the player presses the button (pulling Pin 2 LOW)
  while (digitalRead(buttonPin) == HIGH) {
    // Actively polling the pin loop, waiting for the reaction event
  }
  
  unsigned long buttonPressedTime = millis();
  digitalWrite(targetLED, LOW); // Extinguish signal LED
  
  // 4. Calculate the time difference metrics and log down to the millisecond
  unsigned long totalReactionTime = buttonPressedTime - signalTriggeredTime;
  
  Serial.print(">>> SIGNAL ACKNOWLEDGED! Reflex Reaction Time: ");
  Serial.print(totalReactionTime);
  Serial.println(" ms <<<");
  
  // Delay buffer window to allow user to release physical button comfortably
  delay(4000);
}
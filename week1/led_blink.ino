int blinkCount = 0;
const int potPin = A0; 

void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin); 
  int blinkDelay = map(potValue, 0, 1023, 100, 2000); 

  digitalWrite(9, HIGH);
  delay(blinkDelay);
  digitalWrite(9, LOW);
  delay(blinkDelay);
  
  blinkCount++;
  Serial.print("Blink count: ");
  Serial.print(blinkCount);
  Serial.print(" | Delay: ");
  Serial.concat(blinkDelay);
  Serial.println("ms");
}
/**
 * @file seven_segment.ino
 * @author Gauransh Pundir
 * @date 2026-06-28
 * @description Week 1 Q3 - Decade counter (0-9) driven on a Common Cathode 
 * 7-segment display using a custom active-HIGH bitmask matrix array.
 */

// Mapping Arduino Pins to Segments: {a, b, c, d, e, f, g}
const int segmentPins[7] = {7, 6, 5, 4, 3, 2, 8};

// 2D Binary Matrix defining representations for digits 0 through 9
// Order matching: {a, b, c, d, e, f, g}
const byte numPatterns[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  // Initialize all segment pins as digital outputs
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW); // Turn off all segments initially
  }
}

void displayDigit(int digit) {
  // Write the corresponding bitmask values out to the pins
  for (int segment = 0; segment < 7; segment++) {
    digitalWrite(segmentPins[segment], numPatterns[digit][segment]);
  }
}

void loop() {
  // Loop through digits 0 to 9, waiting 1 second on each
  for (int count = 0; count <= 9; count++) {
    displayDigit(count);
    delay(1000);
  }
}
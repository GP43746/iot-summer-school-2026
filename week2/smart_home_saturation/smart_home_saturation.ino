/**
 * @file smart_home_saturation.ino
 * @author Gauransh Pundir
 * @date 2026-06-28
 * @description Week 2 Q10 - Saturated hardware automation integration matrix.
 * Exercises concurrent peripheral processing across all digital and analog lines.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x26, 16, 2);
Servo gateServo;

// Complete Pin Mapping Directory
const int buttonOn = 2;   // System Activation Button
const int buttonOff = 3;  // System Deactivation Button
const int buzzerPin = 4;  // Acoustic Alarm Annunciator
const int redPin = 5;     // RGB Red Channel
const int greenPin = 6;   // RGB Green Channel
const int bluePin = 7;    // RGB Blue Channel
const int statusLed = 8;  // Heartbeat Power LED Indicator
const int servoPin = 9;   // Servo Pulse Width Channel
const int trigPin = 10;   // Ultrasonic Transmit Pulse Out
const int echoPin = 11;   // Ultrasonic Echo Capture Input
const int alarmLed = 13;  // Primary Alarm Flash Indicator

const int potPin = A0;    // Manual Override Potentiometer
const int ldrPin = A1;    // Ambient Lux Intensity Sensor
const int tempPin = A2;   // TMP36 Analog Temperature Node

bool systemEnabled = true;

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SMART HOME");
  delay(2000);

  pinMode(buttonOn, INPUT_PULLUP);
  pinMode(buttonOff, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(statusLed, OUTPUT);
  pinMode(alarmLed, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  gateServo.attach(servoPin);
  lcd.clear();
}

void loop()
{
  // Check Activation Inputs
  if(digitalRead(buttonOn) == LOW)
  {
    systemEnabled = true;
    delay(200); // Contact bounce stabilization
  }

  if(digitalRead(buttonOff) == LOW)
  {
    systemEnabled = false;
    delay(200); // Contact bounce stabilization
  }

  // Safe Mode / Disabled System Routing State
  if(!systemEnabled)
  {
    digitalWrite(statusLed, LOW);
    digitalWrite(alarmLed, LOW);
    digitalWrite(buzzerPin, LOW);

    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255); // Solid blue indicates disabled state

    lcd.setCursor(0, 0);
    lcd.print("SYSTEM OFF     ");
    lcd.setCursor(0, 1);
    lcd.print("Press ON Btn   ");
    return;
  }

  digitalWrite(statusLed, HIGH);

  // 1. Process Manual Servo Position Loop
  int potValue = analogRead(potPin);
  int servoAngle = map(potValue, 0, 1023, 0, 180);
  gateServo.write(servoAngle);

  // 2. Gather Environmental Sensor Telemetry
  int lightValue = analogRead(ldrPin);
  int sensorValue = analogRead(tempPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;

  // 3. Trigger Ultrasonic Echo Measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2.0;

  bool alarm = false;

  // 4. Evaluate Integrated Security Safety Boundaries
  if(temperature > 35.0 || distance < 20.0)
  {
    alarm = true;
  }

  // 5. Execute Action State Output Matrix
  if(alarm)
  {
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(alarmLed, HIGH);
  }
  else
  {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(alarmLed, LOW);
  }

  // 6. Update Local Alpha-Numeric Screen Channels
  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print((int)temperature);
  lcd.print("C D:"); lcd.print((int)distance);
  lcd.print("    ");

  lcd.setCursor(0, 1);
  lcd.print("L:"); lcd.print(lightValue);
  lcd.print(" S:"); lcd.print(servoAngle);
  lcd.print("    ");

  // 7. Output Unified Packets across the Serial telemetry stream
  Serial.print("Temp: ");     Serial.print(temperature);
  Serial.print(" Light: ");    Serial.print(lightValue);
  Serial.print(" Distance: "); Serial.print(distance);
  Serial.print(" Servo: ");    Serial.println(servoAngle);

  delay(300); // Main loop timing regulator
}
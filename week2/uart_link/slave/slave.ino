/**
 * @file slave.ino
 * @author Gauransh Pundir
 * @date 2026-06-28
 * @description Week 2 Q9 - UART Inter-Processor Link (Slave Node). 
 * Captures string arrays over the RX channel buffer and acts as an index 
 * controller to adjust a mechanical servo barrier gate.
 */

#include <Servo.h>

Servo gateServo;
String command = "";

void setup()
{
  Serial.begin(9600); // Initialize hardware serial port at matched baud speed
  gateServo.attach(9);
  gateServo.write(0);  // Initialize the gate barrier to default closed posture (0 degrees)
}

void loop()
{
  // Constantly monitor if processing data packets sit in the internal buffer
  if(Serial.available())
  {
    // Read buffer string up to the newline character passed by the master node
    command = Serial.readStringUntil('\n');
    command.trim(); // Strip invisible carriage return spaces

    if(command == "OPEN")
    {
      gateServo.write(90); // Actuate gate angle out to 90 degrees
      Serial.println("Gate Opened");
    }
    else if(command == "CLOSE")
    {
      gateServo.write(0);   // Reset gate position back to baseline
      Serial.println("Gate Closed");
    }
  }
}
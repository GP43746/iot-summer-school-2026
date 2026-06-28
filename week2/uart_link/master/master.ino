/**
 * @file master.ino
 * @author Gauransh Pundir
 * @date 2026-06-28
 * @description Week 2 Q9 - UART Inter-Processor Link (Master Node). 
 * Tracks edge transitions on an input push button and transmits state flags 
 * asynchronously over the TX hardware serial channel.
 */

const int buttonPin = 2;
bool lastState = LOW;

void setup()
{
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); // Open the UART interface line at 9600 baud
}

void loop()
{
  bool currentState = digitalRead(buttonPin);

  // State change edge-detection filter
  if(currentState != lastState)
  {
    if(currentState == HIGH)
    {
      // Push the standard string command with a trailing newline terminator
      Serial.println("OPEN");
    }
    else
    {
      Serial.println("CLOSE");
    }

    lastState = currentState;
    delay(50); // Software debounce filter to lock contact stabilization
  }
}
/**
 * @file smart_street_light.ino
 * @author Gauransh Pundir
 * @date 2026-06-28
 * @description Week 1 Q5 - Smart street light system utilizing an LDR voltage 
 * divider array to toggle a digital pin based on customized sensor constants.
 */

const int LED = 9;
const int PHOTORESISTOR = A0;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(PHOTORESISTOR, INPUT);
  Serial.begin(9600);
  digitalWrite(LED, LOW);
}

void loop()
{
  int PHOTO_VALUE = analogRead(PHOTORESISTOR);
  Serial.println(PHOTO_VALUE);
  
  if (PHOTO_VALUE < 300){
    digitalWrite(LED, HIGH);
    delay(1000); // 1-second operational hold phase
  }
  else {
    digitalWrite(LED, LOW);
    delay(1000); // 1-second operational hold phase
  }
}
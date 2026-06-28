/**
 * @file i2c_lcd.ino
 * @author Gauransh Pundir
 * @date 2026-06-28
 * @description Week 2 Q7 - Character LCD integration via the I2C synchronous 
 * serial communication bus using specialized LiquidCrystal_I2C initialization.
 */

#include <LiquidCrystal_I2C.h>

// Initialize the 16x2 display configuration at I2C address 0x26
LiquidCrystal_I2C lcd(0x26, 16, 2);

void setup()
{
  Serial.begin(9600);
  lcd.init();					
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("GAURANSH PUNDIR");
}

void loop()
{
  // The loop remains empty as this is a static string display task
}
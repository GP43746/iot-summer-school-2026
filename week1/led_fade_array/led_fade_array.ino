/**
 * @file led_fade_array.ino
 * @author Gauransh Pundir
 * @date 2026-06-28
 * @description Week 1 Q1 - Re-engineered PWM LED fading array with conditional 
 * index-based loop repetitions and optimized speed profiles.
 */

int leds[] = {11, 10, 9, 6, 5, 3};

void setup()
{
  for(int i = 0; i < 6; i++)
  {
    pinMode(leds[i], OUTPUT);
  }
}

void loop()
{
  for(int i = 0; i < 6; i++)
  {
    int repetitions;

    // Even indexes (0, 2, 4) execute twice; Odd indexes (1, 3, 5) execute once
    if(i % 2 == 0)
    {
      repetitions = 2;
    }
    else
    {
      repetitions = 1;
    }

    for(int j = 0; j < repetitions; j++)
    {
      for(int b = 0; b <= 255; b++)
      {
        analogWrite(leds[i], b);
        delay(1); // Rapid acceleration curve
      }

      for(int b = 255; b >= 0; b--)
      {
        analogWrite(leds[i], b);
        delay(1); // Rapid deceleration curve
      }
    }
  }
}
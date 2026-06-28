/**
 * @file led_matrix.ino
 * @author Gauransh Pundir
 * @date 2026-06-28
 * @description Week 1 Q2 - Multiplexed 4x4 LED Matrix display system utilizing 
 * Persistence of Vision (POV) scanning to display user initials ('G').
 */

int rows[4] = {2, 3, 4, 5};
int cols[4] = {6, 7, 8, 9};

// 4x4 Binary pattern mapping out the structural representation of the letter 'G'
byte G[4][4] =
{
  {1, 1, 1, 0},
  {1, 0, 0, 0},
  {1, 0, 1, 1},
  {0, 1, 0, 1}
};

void setup()
{
  for(int i = 0; i < 4; i++)
  {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
    
    // Default state: Keep all rows HIGH to ensure LEDs start turned off
    digitalWrite(rows[i], HIGH);
    digitalWrite(cols[i], LOW);
  }
}

void displayPattern(byte pattern[4][4], int duration)
{
  unsigned long startTime = millis();

  while(millis() - startTime < duration)
  {
    for(int r = 0; r < 4; r++)
    {
      for(int c = 0; c < 4; c++)
      {
        if(pattern[r][c] == 1)
        {
          // Multiplexing strobe phase
          digitalWrite(rows[r], LOW);   // Sink current (Row ON)
          digitalWrite(cols[c], HIGH);  // Source current (Column ON)

          delay(1); // Brief delay window for micro-strobe illumination

          // Ground discharge phase to prevent visual ghosting across pixels
          digitalWrite(rows[r], HIGH);
          digitalWrite(cols[c], LOW);
        }
      }
    }
  }
}

void loop()
{
  displayPattern(G, 1000);
}
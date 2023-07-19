
#include <LiquidCrystal.h>
int seconds = 0;
int LDR = A3;
LiquidCrystal lcd_1(4, 6, 11, 12, 13, 14);

void setup()
{
  Serial.begin(9600);
  pinMode(LDR, INPUT);
  lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.

  // Print a message to the LCD.
  
}

void loop()
{
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting
  // begins with 0):
  int y = analogRead(LDR);
 
  lcd_1.setCursor(0, 1);
  Serial.println(y);
  // print the number of seconds since reset:
 
  delay(1000); // Wait for 1000 millisecond(s)
  seconds += 1;
}

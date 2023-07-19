
#include <LiquidCrystal.h>
int seconds = 0;
int LDR = A3;
int Threshold = 2.5;
int led =13;
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

void setup()
{
  pinMode(led, OUTPUT);
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
  int t = map(y,0,605,0,5);
  if(t>Threshold)
  {digitalWrite(13, HIGH);
   lcd_1.setCursor(0,1);
   lcd_1.print("LED :ON");
   Serial.println("LED :ON");
  }
  else
  {
   digitalWrite(13, LOW);
   lcd_1.setCursor(0,1);
   lcd_1.print("LED :OFF");
   Serial.println("LED :OFF");
  }
  lcd_1.setCursor(0, 0);
  Serial.println(t);
  // print the number of seconds since reset:
  lcd_1.print(t);
  delay(1000); // Wait for 1000 millisecond(s)
  seconds += 1;
}

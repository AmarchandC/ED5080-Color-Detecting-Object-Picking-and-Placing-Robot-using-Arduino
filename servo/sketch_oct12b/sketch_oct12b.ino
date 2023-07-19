// C++ code
//
/*
  Sweep

  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep

  servo_9.write(pos);
  // sweep the servo from 0 to 180 degrees in steps
  // of 1 degrees
  for (pos = -30; pos <= 30; pos += 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    delay(150);
    // wait 15 ms for servo to reach the position
  }
  servo_9.write(pos);
  delay(2500);
    
*/

#include <Servo.h>

int pos = 0;

Servo servo_9;

void setup()
{
  servo_9.attach(6);
}

void loop()
{
   for (pos = 0; pos <= 30; pos += 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    delay(15);
    
    // wait 15 ms for servo to reach the position
  }
  servo_9.detach();
  delay(500);
 
    // wait 15 ms for servo to reach the position
  }
  

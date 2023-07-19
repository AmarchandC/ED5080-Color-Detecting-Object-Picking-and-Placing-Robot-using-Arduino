//Manual Calibration Code ;
#define LDR A2
#include <Servo.h>
int a = 0;
int i = 0;
Servo servo1;
int servopin = 5;
int ledpin[] = {9, 10, 11};
int rgb[] = {0, 0, 0};
int white[] = {0, 0, 0};
int input = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(7, INPUT_PULLUP);
  servo1.attach(servopin);
  Serial.begin(9600);
  Serial.println("Press 1 to end the calibration");



}

void loop() {
  //press the button to manual calibrate.

  // put your main code here, to run repeatedly:
  servo1.write(i);
  delay(50);
  ColorDetection();

  input = Serial.parseInt();
  while (input == 1)
  {
    exit(0);
  }
  i = i + 2;
}
void ColorDetection()
{

  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  white[0] = analogRead(LDR);

  delay(100);
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(11, LOW);
  white[1] = analogRead(LDR);

  delay(100);
  digitalWrite(11, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  white[2] = analogRead(LDR);

  if (abs(white[0] - white[1]) < 40 && abs(white[1] - white[2]) < 40 && abs(white[2] - white[0]))
  {
    Serial.println("WHITE");
  }
  else if (white[1] > white[2] && white[2] > white[0]) //gbr
  {
    Serial.println("BLUE");
  }
  else if (white[1] > white[0] && white[0] > white[2] ) //grb
  {
    Serial.println("GREEN");
  }
  else if (white[2] < white[0] && white[0] < white[1])
  {
    Serial.println("RED");
  }





  Serial.println("R :" + (String)white[0] + " G :" + (String)white[1] + " B :" + (String)white[2]);
  delay(100);



}

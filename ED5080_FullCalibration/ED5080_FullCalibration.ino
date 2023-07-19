#include <LiquidCrystal.h>
#define LDR A2
const int rs = 2, en = 3, d4 = 4, d5 = 8, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int key1 = 0;
#include <Servo.h>
int white[] = {0, 0, 0};
int step = 2;
/*maximum intensities*/
/*int Red_int = 200;
int Green_int = 200;
int Blue_int = 200;
*/
int cal = 0;
int maximum = 0;
int key = 1;
int red = 9;
int green = 10;
int blue = 11;

int ldr1 = 0;
int ldr2 = 0;
int ldr3 = 0;

int i = 1;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  delay(100);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  pinMode(A2, INPUT);
  lcd.begin(16, 2);
}


void ManualCalibrate()
{


  while (key1 == 0)
  {
    key1 = Serial.parseInt();
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    white[0] = analogRead(LDR);

    delay(500);
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(11, LOW);
    white[1] = analogRead(LDR);

    delay(500);
    digitalWrite(11, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    white[2] = analogRead(LDR);

    Serial.println("R :" + (String)white[0] + " G :" + (String)white[1] + " B :" + (String)white[2]);
    delay(500);

  }
  if (key1 == 2)
  {
    Serial.println("Done Manual");
  }

}

void AutoCalibrate() {
  int Red_int=245;
  int Green_int=245;
  int Blue_int=245;
  while (key == 1) {

    analogWrite(red, Red_int);
    ldr1 = analogRead(A2);
    delay(100);
    analogWrite(red, 0);

    analogWrite(green, Green_int);
    ldr2 = analogRead(A2);
    delay(100);
    analogWrite(green, 0);
  
    
    analogWrite(blue, Blue_int);
    ldr3 = analogRead(A2);
    delay(100);
    analogWrite(blue, 0);
  
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("R:");
    lcd.print(ldr1);

    lcd.print("G:");
    lcd.print(ldr2);

    lcd.setCursor(0, 1);
    lcd.print("B:");
    lcd.print(ldr3);
    lcd.display();
    delay(100);

    if (ldr1 > ldr2 && ldr1 > ldr3) {
      maximum = ldr1;
    }
    else if (ldr2 > ldr3) {
      maximum = ldr2;
    }
    else {
      maximum = ldr3;
    }

    if (maximum - ldr1 > 20) {
      Red_int = Red_int - step;
     
    }
    if (maximum - ldr2 > 20) {
      Green_int = Green_int - step;
      
    }
    if (maximum - ldr3 > 20) {
      Blue_int = Blue_int - step;
      
    }
    Serial.println("Red_Int: " + (String)Red_int + "  Green_Int: " + (String)Green_int + "  Blue_Int: " + (String)Blue_int );
    if (maximum - ldr1 < 20 && maximum - ldr2 < 20 && maximum - ldr3 < 20) {
      key = 0;
      Serial.println("AUTOCAL");
      Serial.println("FINAL! Red_Int: " + (String)Red_int + "Green_Int: " + (String)Green_int + "Blue_Int: " + (String)Blue_int );
    }
  }
}

void loop() {

  ////////// Calibration

  Serial.println("Please enter 3 for Manual Calibration and 1 for Auto Calibration");
  while (Serial.available() == 0) {}

  while (Serial.available() > 0) {
    cal = Serial.parseInt();
    Serial.println(cal);
    if (cal == 1) {
      Serial.println("AutoCal Start");
      AutoCalibrate();
      Serial.println("Done Auto");
    }

    else if (cal == 3) {
      Serial.println("Start Manual , press 2 to stop");
      ManualCalibrate();
    }
  }

}


/*void loop(){
intensity() ;}
void intensity() {
  int q = 255;
  while (q > 0) {
    analogWrite(red, q);
    delay(100);
    q = q - 5;

  }
}
*/

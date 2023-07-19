#include <Servo.h>
#include <LiquidCrystal.h>
#define LDR A2



//lcd intiation
const int rs = 2, en = 3, d4 = 4, d5 = 8, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



//servo initiation
Servo servo1;
Servo servo2;
int servoPin1 = 5;
int servoPin2 = 6;



//declaring univarsal veriables for further use
int Color_reached = 0;
int Rprev = 1;
int Gprev = 1;
int Bprev = 1;
int isStateChanged = 0;
char temp;
int t = 0;
char var;
int a = 0;
int ledpin[] = {9, 10, 11};

int white[] = {0, 0, 0};
int input = 0;
int key1 = 0;
int step = 2;

//maximum intensities/
int Red_int = 255;
int Green_int = 255;
int Blue_int = 255;

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
int rgb[] = { -1000, -1000, -1000};
int rgb1[] = { -1000, -1000, -1000};
int rgb2[] = { -1000, -1000, -1000};
bool setNeut = true;
int angle = 90;
int delAngle = 1;
char Color = 'R';
char currColor = 'W';


//setup loop runs at starting once
void setup() {
  //lcd declaration
  lcd.begin(16, 2);

  //servo diclaration
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  //serial monitor declaration
  Serial.begin(9600);

  //declaring  pin modes
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(8, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A1, INPUT);

  //display and ask for calibration options
  lcd.write("Welcome");
  lcd.display();
  delay(2000);
  lcd.clear(); ////////// Calibration
  ////////// Calibration

  Serial.println("\tPlease enter 3 for Manual Calibration and 1 for Auto Calibration");
  while (Serial.available() == 0) {}


  cal = Serial.parseInt();
  Serial.println(cal);
  if (cal == 1) {
    Serial.println("\tAutoCal Start");
    AutoCalibrate();
    Serial.println("\tDone Auto");
  }

  else if (cal == 3) {
    Serial.println("\tStart Manual , press 2 to stop");
    ManualCalibrate();
  }

  Serial.println("\tCalibration completed");
}



void loop() {
  //Ask for input to pick up from where
  Serial.println("\tSeclect pick up location ");
  Serial.println("\tEnter : int 1 for R /int  2 for G / int 3 for B ");
  t = Serial.available();
  while (Serial.available() == t) {}


  cal = Serial.parseInt();
  Serial.println(cal);


  Serial.println("\tdelay start");
  servo1.write(20);
  delay(2000);
  Serial.println("\tdelay done! ");
  int Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = 0;
  delay(2000);

  if (cal == 1) {
    Serial.println("detection Start R");
    for (int c = 20; c < 180; c++) {
      servo1.write(c);
      int Color_reached_loop = getColor();
      if (Color_reached_loop == 1) {
        Serial.println("Reached Red");
        delay(2000);
        //will pick from already reached color position
        pickup();
        delay(2000);
        break;
      }
    }
    delay(2000);
    Serial.println("detection over");
  }
  if (cal == 2 ) {
    Serial.println("detection Start G");
    for (int z = 20; z < 180; z++) {
      servo1.write(z);
      int Color_reached_loop = getColor();
      if (Color_reached_loop == 2) {
        Serial.println("Reached green");
        delay(2000);
        //will pick from already reached color position
        pickup();
        delay(2000);
        break;
      }
    }
    delay(2000);
    Serial.println("detection over");
  }
  if (cal == 3 ) {
    Serial.println("detection Start B");
    for (int y = 20; y < 180; y++) {
      servo1.write(y);
      int Color_reached_loop = getColor();
      if (Color_reached_loop == 3) {
        Serial.println("Reached Blue");
        delay(2000);
        //will pick from already reached color position
        pickup();
        delay(2000);
        break;
      }
    }
    delay(2000);
    Serial.println("detection over");
  }
  Serial.println("out of detection over function");
  //will return to nutral position
  delay(100);
  neutralposition();
  delay(100);
  //asking for drop location
  Serial.println("Seclect drop location");
  Serial.println("enter : int 1 for R /int  2 for G / int 3 for B");
  t = Serial.available();
  while (Serial.available() == t) {}

  cal = Serial.parseInt();
  Serial.println(cal);
  Serial.println("\tdelay start");
  servo1.write(20);
  delay(2000);
  Serial.println("\tdelay done!");
  Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = getColor();
  Color_reached_loop = 0;
  delay(2000);

  if (cal == 1) {
    Serial.println("detection Start R");
    for (int c = 20; c < 180; c++) {
      servo1.write(c);
      if (getColor() == 1) {
        Serial.println("Reached Red");
        break;
      }
    }
    delay(2000);
    Serial.println("detection over");
  }
  if (cal == 2 ) {
    Serial.println("detection Start G");
    for (int z = 20; z < 180; z++) {
      servo1.write(z);
      if (getColor() == 2) {
        
        Serial.println("Reached green");
        
        break;
      }
    }
    delay(2000);
    Serial.println("detection over");
  }
  if (cal == 3 ) {
    Serial.println("detection Start B");
    for (int y = 20; y < 180; y++) {
      servo1.write(y);
      if (getColor() == 3) {
        Serial.println("Reached Blue");
        break;
      }
    }
    delay(2000);
    Serial.println("detection over");
  }
  
  Serial.println("Got drop location input");
  delay(500);
  drop();
  servo1.write(180);
  delay(1000);
  neutralposition();
  Serial.println("at neutral position");
}




//pickup function
void pickup() {
  //for moving arm down
  int j = 0;
  for (j = 90; j < 180; j++) {
    servo2.write(j);
    if (digitalRead(A1) == LOW) {
      break;
    }
    delay(100);
  }
  Serial.println("completed arm down");
  //delay for getting magnet input on
  digitalWrite(7, HIGH);
  //operation delay
  Serial.println("delay to stick object started ");
  delay(5000);
  Serial.println("delay to stick object ended");
  //returning back arm to upper position
  Serial.println("returning back up");
  for (j = j; j > 90; j = j - 1) {
    servo2.write(j);
    delay(100);
  }
  Serial.println("completed pickup");
}



//go to neutral funtion defination
void neutralposition() {
  Serial.println("started moving to neutral position ");
  servo1.write(135);
  servo2.write(90);
  Serial.println("Reached neutral postion");
}



//drop funtion defination
void drop() {
  //for moving arm down
  int j = 0;
  for (j = 90; j < 180; j++) {
    servo2.write(j);
    if (digitalRead(A1) == LOW) {
      break;
    }
    delay(100);
  }
  Serial.println("completed arm down");
  //delay for getting magnet input on
  digitalWrite(7, LOW);
  Serial.println("delay to drop object started ");
  delay(5000);
  Serial.println("delay to drop object ended");
  //returning back arm to upper position
  Serial.println("returning back up");
  for (j = j; j > 90; j = j - 1) {
    servo2.write(j);
    delay(100);
  }
  Serial.println("completed drop");
}

//code to autocalibrate
void AutoCalibrate() {
  while (key == 1) {
    analogWrite(red, Red_int);
    delay(100);
    ldr1 = analogRead(A2);
    analogWrite(red, 0);

    analogWrite(green, Green_int);
    delay(100);
    ldr2 = analogRead(A2);
    analogWrite(green, 0);

    analogWrite(blue, Blue_int);
    delay(100);
    ldr3 = analogRead(A2);
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

//code to manually calibrate
void ManualCalibrate() {


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
//
////take input function
//int takeInput() {
//  Serial.println("in take input");
//  int R = digitalRead(7);
//  if ( Rprev != R) {
//    R = 1;
//    digitalWrite(11, HIGH);
//    isStateChanged = 1;
//    Serial.println("R");
//    Serial.println(isStateChanged);
//    temp = "R";
//  }
//  Rprev = R;
//
//  int G = digitalRead(8);
//  if ( Gprev != G) {
//    G = 1;
//    digitalWrite(12, HIGH);
//    isStateChanged = 1;
//    Serial.println("G");
//    Serial.println(isStateChanged);
//    temp = "G";
//  }
//  Gprev = G;
//
//  int B = digitalRead(9);
//  Serial.println(B);
//  if ( Bprev != B) {
//    B = 1;
//    Serial.println(B);
//    digitalWrite(13, HIGH);
//    isStateChanged = 1;
//    Serial.println("B");
//    Serial.println(isStateChanged);
//    temp = "B";
//  }
//  Bprev = B;
//  return temp;
//}


int getColor()
{

  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  rgb[0] = analogRead(LDR);

  delay(100);
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(11, LOW);
  rgb[1] = analogRead(LDR);

  delay(100);
  digitalWrite(11, HIGH);
  digitalWrite(9, LOW);
  digitalWrite( 10, LOW);
  rgb[2] = analogRead(LDR);


  //Serial.println((String)rgb[0] + ":" + (String)rgb[1] + ":" + (String)rgb[2]);
  //Serial.println((String)rgb1[0] + ':' + (String)rgb1[1] + ':' + (String)rgb1[2]);
  //Serial.println((String)rgb2[0] + ':' + (String)rgb2[1] + ":" + (String)rgb2[2]);


  if (rgb1[0] > 600 && rgb1[1] > 600 && rgb1[2] > 600)
  {
    //Serial.println("Not White");
    if (rgb1[0] > rgb[0] || rgb1[1] > rgb[1] || rgb1[2] > rgb[2])
    {
      if (rgb1[0] > rgb2[0] || rgb1[1] > rgb2[1] || rgb1[2] > rgb2[2])
      {
        if ((rgb[1] > rgb[2] && rgb[2] > rgb[0]) || rgb[2] > 800)
        {
          Serial.print("\tBlue!");
          Color_reached = 3;
        }
        else if (rgb[1] > rgb[0] && rgb[0] > rgb[2] && rgb[0] > 650)
        {
          Serial.print("\tGreen!");
          Color_reached = 2;
        }
        else if (rgb[0] > rgb[2] && rgb[2] > rgb[1] && rgb[0] > 700)
        {
          Serial.print("\tRed!");
          Color_reached = 1;
        }
        else {
          Color_reached = 0;
        }
        //
        //        Serial.println((String)rgb[0] + ":" + (String)rgb[1] + ":" + (String)rgb[2]);
        //        Serial.println((String)rgb1[0] + ':' + (String)rgb1[1] + ':' + (String)rgb1[2]);
        //        Serial.println((String)rgb2[0] + ':' + (String)rgb2[1] + ":" + (String)rgb2[2]);
      }
    }
  }

  rgb2[0] = rgb1[0];
  rgb2[1] = rgb1[1];
  rgb2[2] = rgb1[2];

  rgb1[0] = rgb[0];
  rgb1[1] = rgb[1];
  rgb1[2] = rgb[2];
  return Color_reached;
}


void getColorPos() //char currColor, char Color
{

  delay(100);
  if (setNeut)
  {
    angle = 45;
    setNeut = false;
  } else
  {
    if (currColor == Color)
    {
      //pickUp();
      setNeut = true;
      return;
      Serial.println("Got Color Position");
    } else
    {

      if (angle >= 200)
      {
        delAngle = -2;
      } else if (angle <= 50)
      {
        delAngle = 2;
      }

      angle += delAngle;
    }

  }

  servo1.write(angle);
  delay(100);
}

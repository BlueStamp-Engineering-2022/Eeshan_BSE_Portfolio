#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <LiquidCrystal_I2C.h>
#include <SoftwareServo.h>

SoftwareServo panservo;
SoftwareServo tiltservo;
SoftwareServo leftbrowservo;
SoftwareServo rightbrowservo;
LiquidCrystal_I2C lcd(0x27,20,4);
Adafruit_8x16matrix matrix = Adafruit_8x16matrix();
const int trigPin= 6;
const int echoPin=7;
int duration;
int distance;
void setup() {
  // put your setup code here, to run once:
  lcd.init();                      // initialize the lcd 
  lcd.init();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600);
matrix.begin(0x70);
tiltservo.attach(A2);
panservo.attach(A3);
leftbrowservo.attach(A0);
rightbrowservo.attach(A1);
}
static const uint8_t PROGMEM
  eye_bmp[] =
  { 0b01111110,
    0b10000001,
    0b10000001,
    0b10011001,
    0b10011001,
    0b10000001,
    0b10000001,
    0b01111110 },
  happy_bmp[] =
  { 0b00001111,
  0b00111110,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00100000,
  0b00111110,
  0b00001111 },
  skull_bmp[] =
  { 0b01111000,
    0b11000100,
    0b10110111,
    0b10000011,
    0b10000011,
    0b10110111,
    0b11000100,
    0b01111000 };

void loop() {
  // put your main code here, to run repeatedly:
  //matrix.clear();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  
    lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print(distance);
  delay(10);
  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance <= 5)
  {
    Serial.println("Less than 7");
    matrix.clear();
    matrix.drawBitmap(0,8,skull_bmp,8,8,LED_ON);
    matrix.writeDisplay();
    matrix.drawBitmap(0,0,skull_bmp,8,8,LED_ON);
    matrix.writeDisplay();
    lcd.backlight();
    lcd.setCursor(1,0);
    //lcd.print();
    for(int i = 30; i < 100; i+=2) 
    {
      panservo.write(i);
      SoftwareServo::refresh();
      delay(10);
      tiltservo.write(i);
      SoftwareServo::refresh();
      delay(10);
    }
    for (int i = 100; i > 30; i-=2) 
  {
    panservo.write(i);
    SoftwareServo::refresh();
    delay(10);
    
    tiltservo.write(i);
    SoftwareServo::refresh();
    delay(10);
    
  }
  Serial.println("end of less than 7");
  }
  else if (distance>=5 && distance<=70)
 {
  Serial.println("in here");
    matrix.clear();
    matrix.drawBitmap(0,8,happy_bmp,8,8,LED_ON);
    matrix.writeDisplay();
    matrix.drawBitmap(0,0,happy_bmp,8,8,LED_ON);
    matrix.writeDisplay();
    lcd.backlight();
    lcd.setCursor(1,0);
    //lcd.print();
    panservo.write(69);                  // sets the servo position according to the scaled value
    SoftwareServo::refresh();
    //delay(30);
    tiltservo.write(50);
    SoftwareServo::refresh();
    leftbrowservo.write(15);
    SoftwareServo::refresh();
    rightbrowservo.write(170);
    SoftwareServo::refresh();
    delay(10);
 }
  else{
    Serial.println("else statement");
    matrix.clear();
    matrix.drawBitmap(0,8,eye_bmp,8,8,LED_ON);
    matrix.writeDisplay();
    matrix.drawBitmap(0,0,eye_bmp,8,8,LED_ON);
    matrix.writeDisplay();
    lcd.backlight();
    lcd.setCursor(1,0);
    //lcd.print("come back!");
    delay(10);
  }
  Serial.println(distance);
}

#include <Encoder.h>

Encoder left(17,18);
Encoder right(19,20);
/* move motors constant speed */

int leftMotorPWM = 3; 
int leftMotorForward = 5;
int leftMotorBackward = 4;
int rightMotorPWM = 9;
int rightMotorForward = 8;
int rightMotorBackward = 7;
int STBY = 6;
int led = 13;
int maxVal = 255;
int wait = 250;
unsigned int counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(STBY, OUTPUT);  
  pinMode(led, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);
  digitalWrite(STBY, HIGH); // just need this
}

long positionLeft = -999;
long positionRight = -999;

void loop() {  
  // blink
  /*digitalWrite(led, HIGH);
  delay(wait); 
  digitalWrite(led, LOW);
  delay(wait);*/
  bool forward = true;
  setMotor(maxVal/4, forward, forward);
  
  long newLeft, newRight;
  newLeft = left.read();
  newRight = right.read();
  
  if (newLeft != positionLeft || newRight != positionRight) {
    counter++;
    Serial.print("Count = ");
    Serial.print(counter);
    Serial.print(", Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionLeft = newLeft;
    positionRight = newRight;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both encoders to zero");
    left.write(0);
    right.write(0);
  }
}

void setMotor(int val, boolean left, boolean right) {
  digitalWrite(leftMotorForward, left);
  digitalWrite(leftMotorBackward, !left);
  digitalWrite(rightMotorForward, right);
  digitalWrite(rightMotorBackward, !right);
  
  analogWrite(leftMotorPWM, val);  
  analogWrite(rightMotorPWM, val);
}

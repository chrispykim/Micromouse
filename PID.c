void setup() {

  static int Sum = 0;  // integral stuff
  static int ScaleFactor = SOME_CONSTANT;  // idk
  static int Kp = constantP, Ki = constantI, Kd = constantD;  // gain constants for PID controller 
  static int Threshold = SOME_OTHER_CONSTANT;  // preventing integral windup (idk what to put rn)
  static int previous_error = 0;  // stuff for derivative
  // pin #'s to be changed later
  LeftSensor = 1;
  RightSensor = 2;
  Motor = 3;
  pinMode(LeftSensor,INPUT);  // position left
  pinMode(RightSensor,INPUT);  // position right
  pinMode(Motor,OUTPUT);  // motor pin
}

void loop() {

  PID(); 
}

void PID() {

  int ActualLeft, ActualRight;  // actual distance to wall
  int Error;	 // error variable
  int controllerOutput = 0;  // value sent to motors
  int P,I,D;  // the things for the controllerOutput calculation
  
  ActualLeft = analogRead(LeftSensor); 
  ActualRight = analogRead(RightSensor);  
  Error = ActualLeft-ActualRight;  // error value on which PID actions take place
  
  if (abs(Error) < Threshold) {  // accumulation of error too big
  
    Sum += Error;
  }
  else {
  
    Sum = 0;
  }
    
  P = Error;  // proportional control (P)
  I = Sum;  // integral action control (I)
  D = (Error-previous_error)/dt;  // derivative action control (D)
  previous_error = Error;  // save current value for next time
  controllerOutput = P*Kp + I*Ki + D*Kd;  // weighted sum for motor
  controllerOutput = controllerOutput*ScaleFactor; // scale Drive to be in the range 0-255 

  if (controllerOutput < 0){  // Check which direction to go.
    
    digitalWrite (Direction,LOW);  // Direction is some pin#
  }
  else { // depending on the sign of Error
    
    digitalWrite (Direction,HIGH);
  }
  
  if (abs(controllerOutput)>255) {
    
    controllerOutput=255;
  }
  
  analogWrite (Motor,controllerOutput); 
}
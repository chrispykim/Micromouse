void PID(Position) {

  static int previous_error;  // stuff for derivative
  static int ScaleFactor = SOME_CONSTANT;  // idk
  static int SP = DISTANCE_TO_WALL;  // TBD after we know dimensions of mouse
  static int Actual;  // actual distance to wall
  static int Error;	 // error variable
  static int Kp = constantP, Ki = constantI, Kd = constantD;  // gain constants for PID controller 
  static int Threshold = SOME_OTHER_CONSTANT;  // preventing integral windup (idk what to put rn)
  int controllerOutput = 0;  // value sent to motors
  int P,I,D;  // the things for the controllerOutput calculation
  static int Sum;  // accumulation of errors for integral
  
  Actual = analogRead(Position);  // error obtained from IR sensors
  Error = SP-Actual;  // error value on which PID actions take place
  
  if (abs(Error) < Threshold) {  // accumulation of error too big
  
    Sum += error;
  }
  else {
  
    Sum = 0;
  }
    
  P = error * Kp;  // proportional control (P)
  I = takeIntegral(Sum) * Ki;  // integral action control (I)
  D = takeDerivative(error-previous_error) * Kd;  // derivative action control (D)
  previous_error = error;  // save current value for next time
  controllerOutput = P+I+D;
  controllerOutput = controllerOutput*ScaleFactor; // scale Drive to be in the range 0-255 

  if (controllerOutput < 0){  // Check which direction to go.
    
    digitalWrite (Direction,LOW);  // Direction is some pin#
  }
  else { // depending on the sign of Error
    
    digitalWrite (Direction,HIGH);
  }
  
  if (abs(controllerOutput)>255) {
    
    Drive=255;
  }
  
  analogWrite (Motor,controllerOutput); // Motor is some pin#
}
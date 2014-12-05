void PID(some variables) {

  static int previous_error = 0;
  static int SP = DISTANCE_TO_WALL;  // TBD after we know dimensions of mouse
  static int PV;  // PV (process value) is  actual value
  static int error;	 // error variable
  static int P, I, D = 0;  // proportional(P), integral (I), & derivative(D) control action variables
  static int Kp = constantP, Ki = constantI, Kd = constantD;  // gain constants for PID controller 
  int controllerOutput = 0; 
  
  PV = getError();  // error obtained from IR sensors
  error = SP-PV;  // error value on which PID actions take place
  
  if (error != 0) { 
    
    P = error * Kp;      // proportional control (P)
    I = takeIntegral(error) * Ki;  // integral action control (I) 
    D = takeDerivative(error)*Kd;  // derivative action control (D)
    previous_error = error;
    controllerOutput = P+I+D;
  }

  setSpeed(controllerOutput);
  // adjust voltage to motors
}

void setSpeed(int controllerOutput) {

    
}
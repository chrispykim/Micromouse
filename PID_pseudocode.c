void correct_path(some variables) 
{

  static int previous_error = 0;
  static int SP;                    // SP (set point) is value we want process to be
  static int PV;                    // PV (process value) is  actual value
  static int Kp = someConstant, Ki = someOtherConstant;    // constants for PI stuff (TBD)
  static int error, P, I=0;     // error variables
  int total=0; 
  
  SP = something;
  PV = somethingElse;
  
  error = SP-PV; // error value on which PI actions take place
  
  if (error != 0) { // 
    
    P = error * Kp;
    I = (I+error) * Ki;    
    previous_error = error;
    total = (P+I);
  }

  doSomethingToController(total);
}

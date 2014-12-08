void setup() {

  int Sum = 0;  
  int ScaleFactor = 1;  // TBD
  int Kp = 1, Ki = 1, Kd = 1;  // constants for PID controller (TBD)
  int Threshold = 1;  // TBD
  int previous_error = analogRead(LeftSensor) - analogRead(RightSensor); // error value to initialize
  const int DELAY = 15;  // TBD
  const int LEFT_DEFAULT_SPEED = 1;  // TBD
  const int RIGHT_DEFAULT_SPEED = 1;  // TBD
  const int DISTANCE_TO_WALL = 1;  // TBD
  // pin #'s to be changed later
  LeftSensor = 1;
  RightSensor = 2;
  MotorLeft = 3;
  MotorRight = 4;
  pinMode(LeftSensor,INPUT);  // position left
  pinMode(RightSensor,INPUT);  // position right
  pinMode(MotorLeft,OUTPUT);  // motor left pin
  pinMode(MotorRight,OUTPUT);  // motor right pin
}

void loop() {

  delay(DELAY);
  PID(); 
}

int Integral(int error) {

  if (abs(error) < Threshold) {
    Sum += error;
  }
  else {
    Sum = 0;
  }
  return Sum;
}

void PID() {

  int ActualLeft, ActualRight;  // actual distance to wall
  int controllerOutput = 0;  // value sent to motors
  int P,I,D;  // the things for the controllerOutput calculation
  
  ActualLeft = analogRead(LeftSensor); 
  ActualRight = analogRead(RightSensor);  
  
  if (ActualLeft <= DISTANCE_TO_WALL && ActualRight <= DISTANCE_TO_WALL) {

    P = ActualLeft - ActualRight;
    I = Integral(P);
    D = (P - previous_error)/DELAY;
  } 
  else if (ActualLeft <= DISTANCE_TO_WALL && ActualRight > DISTANCE_TO_WALL) {

    P = (ActualLeft - DISTANCE_TO_WALL)*2;
    I = Integral(P);
    D = (P - previous_error)/DELAY;
  } 
  else if (ActualLeft > DISTANCE_TO_WALL && ActualRight <= DISTANCE_TO_WALL) {

    P = (DISTANCE_TO_WALL - ActualRight)*2;
    I = Integral(P);
    D = (P - previous_error)/DELAY;
  }
  else {

    P = 0;
    I = 0;
    D = 0;
  }

  previous_error = P;  // save current value for next time
  controllerOutput = P*Kp + I*Ki + D*Kd;  // weighted sum for motor
  controllerOutput *= ScaleFactor; // scale Drive to be in the range 0-255 
  constrain(controllerOutput, -255, 255);
    
  analogWrite(MotorLeft,LEFT_DEFAULT_SPEED - controllerOutput);  // not entirely sure what to do here
  analogWrite(MotorRight,RIGHT_DEFAULT_SPEED + controllerOutput);
}
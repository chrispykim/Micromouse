int leftEnc = 17;
int rightEnc = 19;
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

volatile unsigned int lpulse=100000;                      // width of left and right encoder pulses in uS
volatile unsigned int rpulse=100000;                      // width of left and right encoder pulses in uS
volatile unsigned int lcount,rcount;                      // left and right pulse counters to measure distance
volatile byte lflag;                                      // flag indicates when left  encoder changes states
volatile byte rflag;                                      // flag indicates when right encoder changes states
volatile unsigned long ltime;                             // remembers time of left  encoders last state change in uS
volatile unsigned long rtime;                             // remembers time of right encoders last state change in uS

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
  digitalWrite(leftEnc,1);                               // enable pullup resistor for left  encoder sensor
  digitalWrite(rightEnc,1);                               // enable pullup resistor for right encoder sensor
  attachInterrupt(0,Lencoder,CHANGE);                     // trigger left  encoder ISR on state change
  attachInterrupt(1,Rencoder,CHANGE);                     // trigger right encoder ISR on state change
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
  setMotor(maxVal/5, forward, forward);
  delay(1000);
  setMotor(0, forward, forward);
  delay(3000);
  Serial.print(lcount);
  Serial.print(", ");
  Serial.println(rcount);
}

//======================================================= ISR for left encoder =======================================================
void Lencoder()
{
  lpulse=micros()-ltime;                               // time between last state change and this state change
  ltime=micros();                                      // update ltime with time of most recent state change
  lcount++;                                            // increment left motor distance counter
}


//======================================================= ISR for right encoder ======================================================
void Rencoder()
{
  rpulse=micros()-rtime;                               // time between last state change and this state change
  rtime=micros();                                      // update ltime with time of most recent state change
  rcount++;                                            // increment right motor distance counter
}

void setMotor(int val, boolean left, boolean right) {
  digitalWrite(leftMotorForward, left);
  digitalWrite(leftMotorBackward, !left);
  digitalWrite(rightMotorForward, right);
  digitalWrite(rightMotorBackward, !right);
  
  analogWrite(leftMotorPWM, val);  
  analogWrite(rightMotorPWM, val);
}

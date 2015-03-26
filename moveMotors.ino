/* move motors constant speed */

int motorPin = 3;   // potentiometer connected to analog pin 3
int led = 13;
int maxVal = 255;
int wait = 250;

void setup() {
  //pinMode(motorPin, OUTPUT);   // sets the pin as output
  //pinMode(led, OUTPUT);
}



void loop() {
  /*digitalWrite(led,HIGH);
  delay(wait); 
  digitalWrite(led,LOW);
  delay(wait);*/
  analogWrite(ledPin, maxVal/2);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
}


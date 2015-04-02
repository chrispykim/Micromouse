/*
 Test the sensors
*/

// Pin 13 LED
// Pin 14 Analog in for sensor
int led = 13;
int leftSensor = 14;


void setup() {
  //Serial.begin(38400);
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(leftSensor, INPUT);
}

int sensorValue;
int wait = 250;
int counter = 0;
float total = 0.0;

void loop() {
  counter++;
  sensorValue = analogRead(leftSensor);
  float voltage = sensorValue * (5.0/1023.0);
  total += sensorValue;
  /* blink while taking readings */
  digitalWrite(led,HIGH);
  delay(wait); 
  digitalWrite(led,LOW);
  delay(wait);
  /* print out average of 10 readings */
  Serial.println(sensorValue);
  //Serial.println(voltage);
  //Serial.print(",");
  if (counter == 10) {
    float avg = total/10.0;
    counter = 0;
    total = 0;
    Serial.print(avg);
    Serial.println(",");
    //delay(5000);
  }
}

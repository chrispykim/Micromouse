/*
 Test the sensors
*/

// Pin 13 LED
// Pin 14 Analog in for sensor
int led = 13;
int leftSensor = 16;
int frontSensor = 15;
int rightSensor = 14;

void setup() {
  //Serial.begin(38400);
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(leftSensor, INPUT);
  pinMode(frontSensor, INPUT);
  pinMode(rightSensor, INPUT);
}

int sensorValue1;
int sensorValue2;
int sensorValue3;
int wait = 500;
int counter = 0;
float total = 0.0;

void loop() {
  counter++;
  sensorValue1 = analogRead(rightSensor);
  sensorValue2 = analogRead(frontSensor);
  sensorValue3 = analogRead(leftSensor);
  //float voltage = sensorValue * (5.0/1023.0);
  //total += sensorValue;
  /* blink while taking readings */
  digitalWrite(led,HIGH);
  delay(wait); 
  digitalWrite(led,LOW);
  delay(wait);
  /* print out average of 10 readings */
  Serial.print("14: ");
  Serial.print(sensorValue1);
  Serial.print(", 15: ");
  Serial.print(sensorValue2);
  Serial.print(", 16: ");
  Serial.print(sensorValue3);
  Serial.println();
  
  /*if (counter == 10) {
    float avg = total/10.0;
    counter = 0;
    total = 0;
    Serial.print("avg =");
    Serial.println(avg);
    //delay(5000);
  }*/
}

#include <Servo.h>

Servo myServo;  
const int servoPin = 9;
const int trigPin = 8;
const int echoPin = 7;


long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);  
  myServo.attach(servoPin); 
  Serial.begin(9600);       
}

void loop() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  duration = pulseIn(echoPin, HIGH);

 
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500); 

  for (int pos = 0; pos <= 180; pos += 1) { 
    myServo.write(pos);              
    delay(15);                       
  }
  for (int pos = 180; pos >= 0; pos -= 1) { 
    myServo.write(pos);              
    delay(15);                       
  }
}

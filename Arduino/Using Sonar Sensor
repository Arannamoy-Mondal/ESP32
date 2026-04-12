#include <Servo.h>

#define trigPin 13
#define echoPin 12

#define whiteLED 10
#define redLED 7
#define orangeLED 6
#define signalPin 11
Servo myServo;

long duration;
int distance;

void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(whiteLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);

  myServo.attach(signalPin);

  Serial.begin(9600);
}

void loop() {

  // Ultrasonic trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // Distance logic

  if (distance > 40) {

    digitalWrite(whiteLED, HIGH);
    digitalWrite(orangeLED, LOW);
    digitalWrite(redLED, LOW);

    myServo.write(0);
  }

  else if (distance > 20) {

    digitalWrite(whiteLED, LOW);
    digitalWrite(orangeLED, HIGH);
    digitalWrite(redLED, LOW);

    myServo.write(90);
  }

  else {

    digitalWrite(whiteLED, LOW);
    digitalWrite(orangeLED, LOW);
    digitalWrite(redLED, HIGH);

    myServo.write(180);
  }

  delay(200);
}

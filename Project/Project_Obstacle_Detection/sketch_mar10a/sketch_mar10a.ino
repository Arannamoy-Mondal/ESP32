#include <Servo.h>

#define trigPin 9
#define echoPin 10

#define whiteLED 2
#define redLED 3
#define orangeLED 4

Servo myServo;

long duration;
int distance;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(whiteLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);

  myServo.attach(6);

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
  Serial.println(distance);



  if (distance > 40) {

    digitalWrite(whiteLED, HIGH);
    digitalWrite(orangeLED, HIGH);
    digitalWrite(redLED, HIGH);

    myServo.write(0);
  }

  else if (distance > 20) {

    digitalWrite(whiteLED, HIGH);
    digitalWrite(orangeLED, HIGH);
    digitalWrite(redLED, HIGH);

    myServo.write(90);
  }

  else {

    digitalWrite(whiteLED, HIGH);
    digitalWrite(orangeLED, HIGH);
    digitalWrite(redLED, HIGH);

    myServo.write(180);
  }

  delay(200);

  digitalWrite(whiteLED, LOW);
    digitalWrite(orangeLED, LOW);
    digitalWrite(redLED, LOW);
    delay(200);
    delay(200);delay(200);delay(200);

    digitalWrite(LED_BUILTIN,HIGH);
    delay(2000);
    digitalWrite(LED_BUILTIN,LOW);
    delay(2000);
}
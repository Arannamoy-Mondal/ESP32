#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "Dar";
const char* password = "123456789";

const int trigPin = 5;
const int echoPin = 18;
const int pirPin = 19;
const int servoPin = 13;

Servo myServo;
WebServer server(80);

long duration;
int distance;
bool motionDetected = false;

void handleRoot() {
  String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'>"
                "<style>body{font-family: sans-serif; text-align:center; padding:20px;}"
                ".data{font-size: 20px; color: blue; margin: 10px;}</style></head><body>"
                "<h1>ESP32 Surveillance System</h1>"
                "<div class='data'>Distance: " + String(distance) + " cm</div>"
                "<div class='data'>Motion: " + (motionDetected ? "DETECTED! ⚠️" : "Clear") + "</div>"
                "<p>The sensor will auto-rotate towards motion.</p>"
                "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pirPin, INPUT);
  
  myServo.attach(servoPin);
  myServo.write(90); 

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  
  Serial.println("\nConnected! IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;


  int pirState = digitalRead(pirPin);
  
  if (pirState == HIGH) {
    motionDetected = true;
    Serial.println("Motion detected! Tracking...");
    myServo.write(45); 
  } else {
    motionDetected = false;
    myServo.write(90); 
  }

  delay(200); 
}
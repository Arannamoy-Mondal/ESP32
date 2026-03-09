#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid = "Dar";
const char* password = "123456789";

WebServer server(80);
Servo myServo;

const int trigPin = 5;
const int echoPin = 18;
const int pirPin = 19;
const int servoPin = 13;

int angle = 0;
int dist = 0;
bool motion = false;


String getHTML() {
  String html = "<!DOCTYPE html><html><head><title>ESP32 Radar</title>";
  html += "<style>body{background:#000; color:#0f0; text-align:center; font-family:monospace;}";
  html += "canvas{background:#111; border:2px solid #0f0; border-radius:50% 50% 0 0; width:90%; max-width:500px;}</style></head><body>";
  html += "<h1>ESP32 SMART RADAR</h1>";
  html += "<canvas id='radarCanvas'></canvas>";
  html += "<h3>Angle: <span id='ang'>0</span> | Distance: <span id='dst'>0</span> cm</h3>";
  html += "<h2 id='mot' style='color:red;'></h2>";
  
  html += "<script>";
  html += "const canvas = document.getElementById('radarCanvas'); const ctx = canvas.getContext('2d');";
  html += "canvas.width = 400; canvas.height = 200;";
  html += "setInterval(function(){ fetch('/data').then(r=>r.json()).then(d=>{";
  html += "document.getElementById('ang').innerText = d.a; document.getElementById('dst').innerText = d.d;";
  html += "document.getElementById('mot').innerText = d.m ? '⚠️ MOTION DETECTED' : '';";
  html += "drawRadar(d.a, d.d); }); }, 100);";
  
  html += "function drawRadar(a, d) {";
  html += "ctx.clearRect(0,0,400,200); ctx.strokeStyle='#0f0'; ctx.beginPath(); ctx.arc(200,200,180,Math.PI,2*Math.PI); ctx.stroke();"; // অর্ধবৃত্ত
  html += "let rad = (a * Math.PI) / 180; let x = 200 + 180 * Math.cos(Math.PI - rad); let y = 200 - 180 * Math.sin(Math.PI - rad);";
  html += "ctx.moveTo(200,200); ctx.lineTo(x,y); ctx.stroke();"; // স্ক্যানিং লাইন
  html += "if(d<100){ let ox = 200 + d*1.8 * Math.cos(Math.PI - rad); let oy = 200 - d*1.8 * Math.sin(Math.PI - rad);";
  html += "ctx.fillStyle='red'; ctx.beginPath(); ctx.arc(ox,oy,5,0,2*Math.PI); ctx.fill(); } }"; // বাধা দেখালে লাল বিন্দু
  html += "</script></body></html>";
  return html;
}

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT); pinMode(pirPin, INPUT);
  myServo.attach(servoPin);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  
  server.on("/", [](){ server.send(200, "text/html", getHTML()); });
  server.on("/data", [](){
    String json = "{\"a\":" + String(angle) + ",\"d\":" + String(dist) + ",\"m\":" + String(motion) + "}";
    server.send(200, "application/json", json);
  });
  server.begin();
}

int getDistance() {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void loop() {
  for (int i = 0; i <= 180; i += 2) {
    angle = i; myServo.write(i); dist = getDistance(); motion = digitalRead(pirPin);
    server.handleClient(); delay(50);
  }
  for (int i = 180; i >= 0; i -= 2) {
    angle = i; myServo.write(i); dist = getDistance(); motion = digitalRead(pirPin);
    server.handleClient(); delay(50);
  }
}
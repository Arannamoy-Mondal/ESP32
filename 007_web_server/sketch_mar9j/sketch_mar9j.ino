#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Dar";
const char* password = "123456789";

WebServer server(80);


String lastReceivedMessage = "";
bool showSuccess = false; 

void handleRoot() {
  String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'>"
                "<style>body{font-family: sans-serif; text-align:center; padding:20px;}"
                "input[type='text']{padding:10px; width:80%; max-width:300px; border:1px solid #ccc; border-radius:4px;}"
                "input[type='submit']{padding:10px 20px; background-color:#007bff; color:white; border:none; border-radius:4px; cursor:pointer; margin-top:10px;}"
                ".success-box{background-color:#d4edda; color:#155724; padding:15px; border-radius:4px; margin-top:20px; border:1px solid #c3e6cb; inline-block;}"
                "</style></head><body>"
                "<h2>ESP32 Control Panel</h2>"
                "<form action='/get_input' method='GET'>"
                "<input type='text' name='message' placeholder='Type something...' required><br>"
                "<input type='submit' value='Submit Message'>"
                "</form>";


  if (showSuccess) {
    html += "<div class='success-box'>"
            "<strong>Success!</strong><br>"
            "ESP32 received: " + lastReceivedMessage + 
            "</div>";
    
  
    showSuccess = false; 
  }

  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleInput() {
  if (server.hasArg("message")) {
    lastReceivedMessage = server.arg("message");
    Serial.println("Received: " + lastReceivedMessage);
    showSuccess = true; 
  }
  

  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/get_input", handleInput);

  server.begin();
}

void loop() {
  server.handleClient();
}
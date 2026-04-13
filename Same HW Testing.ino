#define IN1 14
#define IN2 15
#define IN3 13
#define IN4 12
#define FLASH_LED 4

void setup() {
  Serial.begin(115200);
  
  // Motor & LED Pins setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(FLASH_LED, OUTPUT);
  
 ধ
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  digitalWrite(FLASH_LED, LOW);
  
  Serial.println("Hardware Test Started...");
  delay(3000); 
}

void loop() {
  Serial.println("Moving FORWARD...");
  digitalWrite(FLASH_LED, HIGH); 
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  delay(2000); 

  Serial.println("STOP...");
  digitalWrite(FLASH_LED, LOW); 
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  delay(2000);

  Serial.println("Moving BACKWARD...");
  digitalWrite(FLASH_LED, HIGH); 
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  delay(2000);

  Serial.println("STOP...");
  digitalWrite(FLASH_LED, LOW); 
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  delay(2000); ে
}

int sw1=12,sw2=27;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);
  pinMode(sw1,INPUT_PULLUP);
  pinMode(sw2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(sw1)==LOW){
    Serial.println("SW1 is pressed");
    delay(600);
  }
  if(digitalRead(sw2)==LOW){
    Serial.println("SW2 is pressed");
    delay(600);
  }
}

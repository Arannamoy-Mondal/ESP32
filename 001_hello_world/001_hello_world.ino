int i=0;
void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  Serial.print(i);
  Serial.write(i);
  Serial.print("");
  Serial.println("Hello World");
  delay(1000);
  i++;
  

}

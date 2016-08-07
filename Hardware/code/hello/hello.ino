void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  //Serial sent data back to computer
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello World");
  delay(500);
}

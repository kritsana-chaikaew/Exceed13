String inputString = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Transmitting from Serial1 to Serial2");
  Serial1.print("Intel");
  inputChar = "";
  
  while(Serial2.available)
  {
    char inputChar = (char)Serial2.read();

    inputString += inputChar
  }

  Serial.print("Message received from Serial1:");
  Serial.println(inputSring);

  inputString = "";

  Serial.println("Tranmitting from Serial2 to Serial1:");
  Serial.println("Glileo");

  while(Serial1.available)
  {
    char inputChar = (char)Serial1.read();

    inputString += inputChar
  }

  Serial.print("Message received from Serial2:");
  Serial.println(inputSring);

  inputString = "";

  delay(2000);
}

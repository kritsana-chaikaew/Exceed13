//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(0, 1);
void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available())
  {
    Serial1.print(1234);
    delay(1000);
  }
//  if(Serial.available())
//  {
//    int i = Serial1.read();
//    Serial1.print(i);
//    delay(1000);
//  }
}

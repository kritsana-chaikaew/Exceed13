void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  String data0 = Serial.readStringUntil('\n');
  String data1 = Serial1.readStringUntil('\n');
  String data2 = Serial2.readStringUntil('\n');


  Serial.print(data0);
  Serial1.print(data1);
  Serial2.print(data2);
}

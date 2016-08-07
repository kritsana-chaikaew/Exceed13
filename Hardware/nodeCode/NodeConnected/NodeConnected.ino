#include<ServerExceed.h>

WiFiServer server(80); // nodeMCU server : port 80
char ssid[] = "nodeMCU only";
char password[] = "";
char host[] = "10.32.176.4";
int port = 80;
String group = ".exe"; 

ServerExceed mcu(ssid, password, host, port, group, &server);

void setup() {
  Serial.begin(115200);
  mcu.connectServer();
  Serial.print("\n\nIP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(Serial.available()) {
    String data = Serial.readStringUntil('\r');
    Serial.flush();
    mcu.sendDataFromBoardToServer(data);
  }
  mcu.sendDataFromServerToBoard();
}

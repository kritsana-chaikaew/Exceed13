#include <ServerExceed.h>

// Setting for Server
WiFiServer server(80); // nodeMCU server : port 80
char ssid[] = "eXceed 2G";
char password[] = "";
char host[] = "10.32.176.4";
int port = 80;
String group = ".exe";
ServerExceed mcu(ssid, password, host, port, group, &server);

void setup() {
  Serial.begin(115200);
  mcu.connectServer();

}

String data = "";
String blynk_data = "";
String server_data = "testestest";

void loop() {
  if(Serial.available()) {
    data = Serial.readStringUntil('\n');
    data.replace("\n","");
    Serial.flush();

    if(server_data != "") mcu.sendDataFromBoardToServer(server_data);
  }
  mcu.sendDataFromServerToBoard();

}


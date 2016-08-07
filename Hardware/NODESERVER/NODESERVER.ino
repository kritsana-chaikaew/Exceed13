//#define BLYNK_PRINT Serial // Enables Serial Monitor
//#include <ServerExceed.h>
//#include <SPI.h>
//#include <BlynkSimpleEsp8266.h>
//
//// Setting for Server
//WiFiServer server(80); // nodeMCU server : port 80
//char ssid[] = "eXceed 2G";
//char password[] = "";
//char host[] = "10.32.176.4";
//int port = 80;
//String group = ".exe";
//ServerExceed mcu(ssid, password, host, port, group, &server);
//
//// Setting for Blynk
//char auth[] = "270c1e014d4f4ccaa82a5412d69f115d";
//char blynk_host[] = "10.32.176.4";
//int blynk_port = 18442;
//
//void setup() {
//  Serial.begin(115200);
//  mcu.connectServer();
////  Blynk.config(auth, blynk_host, blynk_port);/
////  BLYNK_PRINT.println("\n\n[- nodeMCU -] Connected.");
////  BLYNK_PRINT.print("[- nodeMCU -] IPAddress : ");
////  BLYNK_PRINT.println(WiFi.localIP());
//}
//
//String data = "";
//String blynk_data = "";
//String server_data = "TEST";
//
//void loop() {
//  if(Serial.available()) {
//    server_data = Serial.readStringUntil('\n');
//    //data.replace("\r","");
//    //data.replace("\n","");
//    Serial.flush();
//    //splitData();
//    if(server_data != "") mcu.sendDataFromBoardToServer(server_data);
//  }
//  mcu.sendDataFromServerToBoard();
//  //Blynk.run();
//  //Serial.println("HAHAHA");
//  delay(1000);
//}
//
//void splitData() {
//  server_data = data.substring(0, data.indexOf(":"));
//  blynk_data = data.substring(data.indexOf(":") + 1, data.length());
//}
//
//BLYNK_WRITE(V0) {
//  int val = param.asInt();
//  Serial.println("LED1:"+String(val)); // ส่งค่าผ่าน Serial ไปที่ Galileo
//}
//
//BLYNK_READ(V1) {
//  Blynk.virtualWrite(V1, blynk_data);
//}
//

#include<ServerExceed.h>

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

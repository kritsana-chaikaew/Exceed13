/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * You can use this sketch as a debug tool that prints all incoming values
 * sent by a widget connected to a Virtual Pin 1 in the Blynk App.
 *
 * App project setup:
 *   Slider widget (0...100) on V1
 *
 **************************************************************/

#define BLYNK_PRINT Serial
#include<ESP8266WiFi.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "b2b9f8f96ab649ca83598835cc465a02";

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, "eXceed 2G", "","10.32.176.4", 18442);
}

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V1 Slider value is: ");
  Serial.println(pinValue);
}

BLYNK_WRITE(V2)
{
  int barValue = param.asInt();
  Serial.print("V12 Bar value is: ");
  Serial.println(barValue);
}



void loop()
{
  Blynk.run();
}

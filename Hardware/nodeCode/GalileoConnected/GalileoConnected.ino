#include <pt.h>
#define PT_DELAY(pt, ms, ts) \
    ts = millis(); \
    PT_WAIT_WHILE(pt, millis()-ts < (ms));

struct pt pt_taskSerialEvent;
struct pt pt_taskSendSerial;

String recieve = "";
String data = "";

PT_THREAD(taskSerialEvent(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1){
    if(Serial1.available()) {
      String recieve = Serial1.readStringUntil('\r'); // recieve data
      recieve.replace("\r","");
      recieve.replace("\n","");
      Serial.println(recieve);
    }
    PT_YIELD(pt);
  }
  PT_END(pt);
}

PT_THREAD(taskSendSerial(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1){
    data = "testtest";
    Serial1.println(data); // sent data here
    PT_DELAY(pt, 300, ts);
  }
  PT_END(pt);
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  PT_INIT(&pt_taskSerialEvent);
  PT_INIT(&pt_taskSendSerial);
}

void loop() {
  taskSerialEvent(&pt_taskSerialEvent);
  taskSendSerial(&pt_taskSendSerial);
}

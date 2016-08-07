#include<pt.h>

#define PT_DELAY(pt, ms, ts) \
  ts = millis(); \
  PT_WAIT_WHILE(pt, millis()-ts < (ms));


#define Motion 3

bool isHaveMotion = false;

struct pt pt_taskMotion;

PT_THREAD(taskMotion(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1){
    if( (int)digitalRead(Motion) == 1)
    {
      isHaveMotion = true;
      Serial.println("Some thing is moving");
    }
    else
    {
      isHaveMotion = false;
      Serial.println("Nothing");
    }
    PT_DELAY(pt, 3000, ts);
  }
  PT_END(pt);
}

void setup() {
  Serial.begin(9600);
  pinMode(Motion, INPUT);
  PT_INIT(&pt_taskMotion);
}

void loop() {
  taskMotion(&pt_taskMotion);
}

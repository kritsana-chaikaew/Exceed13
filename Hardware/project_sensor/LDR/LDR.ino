#include<pt.h>

#define LDR A1

#define PT_DELAY(pt, ms, ts) \
  ts = millis(); \
  PT_WAIT_WHILE(pt, millis()-ts < (ms));

bool isLigthOn = false;
int LDRread = 0;

struct pt pt_taskLDR;

PT_THREAD(taskLDR(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1){
    LDRread = analogRead(LDR);
    Serial.print("LDR: ");
    Serial.print(LDRread);
    if(LDRread > 100)
    {
      isLigthOn = true;
      Serial.println(" Litgh On ");
    }
    else
    {
      isLigthOn = false;
      Serial.println(" Light Off");
    }
    PT_DELAY(pt, 1, ts);
  }
  PT_END(pt);
}

void setup() {
  Serial.begin(9600);
  pinMode(LDR, INPUT);
  PT_INIT(&pt_taskLDR);
}

void loop() {
  taskLDR(&pt_taskLDR);
}

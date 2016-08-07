#include<pt.h>

#define PT_DELAY(pt, ms, ts) \
  ts = millis(); \
  PT_WAIT_WHILE(pt, millis()-ts < (ms));

#define Sound A2

bool isHaveSound = false;

int Soundread = 0;

struct pt pt_taskSound;

PT_THREAD(taskSound(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1){
    Soundread = analogRead(Sound);
    Serial.print("Sound: ");
    Serial.print(Soundread,DEC);

    if(Soundread > 77)
    {
      isHaveSound = true;
      //Serial.println(" Some one here!");
    }
    else
    {
      isHaveSound = false;
      //Serial.println(" No body here!");
    }
    
    if(isHaveSound){
      Serial.println("mekon");
      delay(3500);
    } else{
      Serial.println("MAIMEKON");
      delay(500);
    }
    PT_DELAY(pt, 1, ts);
  }
  PT_END(pt);
}


void setup() {
  Serial.begin(9600);
  pinMode(Sound, INPUT);
  PT_INIT(&pt_taskSound);
}

void loop() {
  taskSound(&pt_taskSound);
  //Serial.print("Sound: ");
  //Serial.println(Soundread,DEC);
  delay(50);
 }

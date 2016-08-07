#include<pt.h>

#define Sonic1_Trig 8
#define Sonic1_Echo 9

#define PT_DELAY(pt, ms, ts) \
  ts = millis(); \
  PT_WAIT_WHILE(pt, millis()-ts < (ms));
bool isHaveObj;
int Sonicread1 = 0;

struct pt pt_taskSonic1;

PT_THREAD(taskSonic1(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1){
    readSonic(1);
    PT_DELAY(pt, 1, ts);
  }
  PT_END(pt);
}

void readSonic(int Sonic)
{
  int TRIG_PIN;
  int ECHO_PIN;
  if(Sonic == 1)
  {
    TRIG_PIN = Sonic1_Trig;
    ECHO_PIN = Sonic1_Echo;
  }

  long duration, distanceCm, distanceIn;
 
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN,HIGH);
 
  // convert the time into a distance
  Sonicread1 = duration / 29.1 / 2 ;
 
  if (Sonicread1 <= 0){
    Serial.println("Out of range ");
    Serial.print(Sonicread1);
    Serial.println("cm");
    isHaveObj = true;
  }
  else if(Sonicread1 <= 10) 
  {
    Serial.print("Found Object ");
    Serial.print(Sonicread1);
    Serial.println("cm");
    isHaveObj = true;
  }
  else
  {
    Serial.print("Path is clear ");
    Serial.print(Sonicread1);
    Serial.println("cm");
    isHaveObj = false;
  }
  
}



void setup() {
  Serial.begin(9600);
  pinMode(Sonic1_Trig, OUTPUT);
  pinMode(Sonic1_Echo, INPUT);
  PT_INIT(&pt_taskSonic1);
}

void loop() {
  taskSonic1(&pt_taskSonic1);
  
}

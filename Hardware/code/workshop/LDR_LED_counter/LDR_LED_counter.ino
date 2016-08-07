#define LDR A1
#define LDK A4
#define PT_DELAY(pt, ms, ts) \
  ts = millis(); \
  PT_WAIT_WHILE(pt, millis()-ts < (ms));

struct pt pt_taskAvg;
struct pt pt_taskCheck;
int avg = 0;
boolean isComing = false;
boolean isGoing = false;
boolean isHaveAvg = false;

int average(SENSOR)
{
  if(!isHaveAvg){
    int a, cnt = 0, sum = 0;
    for(cnt = 0; cnt < 100; cnt++)
    {
      a = analogRead(SENSOR);
      sum += a;
    }
    isHaveAvg = true;
    return sum/100;
    
  }
  return avg;
}


//int average()
//{
//  if(!isHaveAvg){
//    int a, cnt = 0, sum = 0;
//    for(cnt = 0; cnt < 100; cnt++)
//    {
//      a = analogRead(LDR);
//      sum += a;
//    }
//    isHaveAvg = true;
//    return sum/100;
//    
//  }
//  return avg;
//}

void Check()
{
  int light = analogRead(LDR);
//  Serial.print("light : ");
//  Serial.println(light);
//  Serial.print("avg*0.8 : ");
//  Serial.println(avg*0.8);
//  Serial.print("avg*1.2 : ");
//  Serial.println(avg*1.2);  
  if(light < avg*0.8)
  {
    Serial.println("comming in");
    isComing = true;
    isHaveAvg = false;
  }
  if(light > 1.2*avg)
  {
    Serial.println("going out");
    isGoing = true;
    isHaveAvg = false;
  }
  if(isComing&&isGoing){
    
    Serial.println("+1");
    isComing  = false;
    isGoing = false;
  }
//  else
//  {
//    Serial.println("IN AVERAGE");
//  }
}


PT_THREAD(taskAvg(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1)
  {
    avg = average();
    PT_DELAY(pt, 1 ,ts);
  }
  PT_END(pt);
}

PT_THREAD(taskCheck(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1)
  {
    Check();
    PT_DELAY(pt, 1 ,ts);
  }
  PT_END(pt);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  PT_INIT(&pt_taskAvg);
  PT_INIT(&pt_taskCheck);

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(percent(analogRead(LDR), avg));

  taskAvg(&pt_taskAvg);
  taskCheck(&pt_taskCheck);
//  Serial.println("hello");
}

//int average()
//{

//  int a, cnt = 0, sum = 0;
//  for(cnt = 0; cnt < 1000; cnt++)
//  {
//    a = analogRead(LDR);
//    sum += a;
//  }
//  return sum/1000;
//}
//
//void Check()
//{
//  if(analogRead(LDR) < avg*0.8)
//  {
//    Serial.println("LOW");
//  }
//  if(analogRead(LDR) > 1.2*avg)
//  {
//    Serial.println("HIGH");
//  }
//  else
//  {
//    Serial.println("IN AVERAGE");
//  }
//}



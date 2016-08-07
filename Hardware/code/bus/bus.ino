#include <pt.h>
#define LDR A1
//String LDR="A1";
//String LDk="A4";
#define LDK A4
#define PT_DELAY(pt, ms, ts) \
  ts = millis(); \
  PT_WAIT_WHILE(pt, millis()-ts < (ms));

struct pt pt_taskAvgLDR;
struct pt pt_taskCheckLDR;
struct pt pt_taskAvgLDK;
struct pt pt_taskCheckLDK;
struct pt pt_taskPassAll;
//struct pt pt_taskPassIn;
//struct pt pt_taskPassOut;

int avgLDR = 0;
int avgLDK = 0;
boolean isComingLDR = false;
boolean isGoingLDR = false;
boolean isHaveAvgLDR = false;

boolean isComingLDK = false;
boolean isGoingLDK = false;
boolean isHaveAvgLDK = false;

String pass = "";
String STR;
int HUMAN = 0, IN = 0, OUT = 0;
int averageLDR()
{
  if(!isHaveAvgLDR){
    int a, cnt = 0, sum = 0;
    for(cnt = 0; cnt < 100; cnt++)
    {
      a = analogRead(LDR);
      sum += a;
    }
    isHaveAvgLDR = true;
    return sum/100;
    
  }
  return avgLDR;
}
/*
int averageLDR(String temp)
{
  if(!isHaveAvgLDR){
    int a, cnt = 0, sum = 0;
    for(cnt = 0; cnt < 100; cnt++)
    {
      a = analogRead(temp);
      sum += a;
    }
    isHaveAvgLDR = true;
    return sum/100;
    
  }
  return avgLDR;
}
*/
int averageLDK()
{
  if(!isHaveAvgLDK){
    int a, cnt = 0, sum = 0;
    for(cnt = 0; cnt < 100; cnt++)
    {
      a = analogRead(LDK);
      sum += a;
    }
    isHaveAvgLDK = true;
    return sum/100;
    
  }
  return avgLDK;
}

void CheckLDR()
{
  int light = analogRead(LDR);
//  Serial.print("light : ");
//  Serial.println(light);
//  Serial.print("avg*0.9 : ");
//  Serial.println(avgLDR*0.9);
//  Serial.print("avg*1.2 : ");
//  Serial.println(avgLDR*1.2);  
  if(light < avgLDR*0.9)
  {
    Serial.print("LDR comming in ");
    if(pass != "")
      Serial.println("pass = " + pass);
    else
      Serial.println("pass = 0");
    isComingLDR = true;
    isHaveAvgLDR = false;
  }
  if(light > 1.2*avgLDR)
  {
    Serial.print("LDR going out ");
    if(pass != "")
      Serial.println("pass = " + pass);
    else
      Serial.println("pass = 0");
    isGoingLDR = true;
    isHaveAvgLDR = false;
  }
  if(isComingLDR&&isGoingLDR){
    
//    Serial.println("+1");
    isComingLDR  = false;
    isGoingLDR = false;
    pass += "1";
  }
//  else
//  {
//    Serial.println("IN AVERAGE");
//  }
}

void CheckLDK()
{
  int light = analogRead(LDK);
//    Serial.print("light : ");
//  Serial.println(light);
//  Serial.print("avgLDK*0.8 : ");
// ; Serial.println(avgLDK*0.8);
//  Serial.print("avgLDK*1.2 : ");
//  Serial.println(avgLDK*1.2);  
  if(light < avgLDK*0.9)
  {
    Serial.print("LDK comming in ");
    if(pass != "")
      Serial.println("pass = " + pass);
    else
      Serial.println("pass = 0");
    isComingLDK = true;
    isHaveAvgLDK = false;
  }
  if(light > 1.2*avgLDK)
  {
    Serial.print("LDK going out ");
    if(pass != "")
      Serial.println("pass = " + pass);
    else
      Serial.println("pass = 0");
    isGoingLDK = true;
    isHaveAvgLDK = false;
  }
  if(isComingLDK&&isGoingLDK){
    
//    Serial.println("+1");
    isComingLDK  = false;
    isGoingLDK = false;
    pass += "2";
  }
}

PT_THREAD(taskAvgLDR(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1)
  {
    avgLDR = averageLDR();
    PT_DELAY(pt, 1 ,ts);
  }
  PT_END(pt);
}

/*PT_THREAD(taskAvgLDR(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1)
  {
    avgLDR = averageLDR(tempLDR);
    PT_DELAY(pt, 1 ,ts);
  }
  PT_END(pt);
}
*/
PT_THREAD(taskAvgLDK(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1)
  {
    avgLDK = averageLDK();
    PT_DELAY(pt, 1 ,ts);
  }
  PT_END(pt);
}

PT_THREAD(taskCheckLDR(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1)
  {
    CheckLDR();
    PT_DELAY(pt, 1 ,ts);
  }
  PT_END(pt);
}

PT_THREAD(taskCheckLDK(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1)
  {
    CheckLDK();
    PT_DELAY(pt, 1 ,ts);
  }
  PT_END(pt);
}


PT_THREAD(taskPassAll(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1)
  {
    if(pass == "12"){
      Serial.println("          Human In!");
      HUMAN++;
      IN++;
//      STR = ("1-%d\n2-%d\n3-%d" ,HUMAN, IN, OUT);
//      STR = "1-" + HUMAN + "\n2-" + IN + "\n3-" + OUT;
      sentData(HUMAN, IN, OUT);
      pass = "";
//      isPassLDR = false;
//      isPassLDK = false;
    }
    else if(pass =="21"){
      Serial.println("          Human Out!");
      HUMAN--;
      OUT++;
//      STR = ("1-%d\n2-%d\n3-%d" ,HUMAN, IN, OUT);
//      STR = "1-" + HUMAN + "\n2-" + IN + "\n3-" + OUT;
      sentData(HUMAN, IN, OUT);
      pass = "";
    }
//    else if(pass != "" && pass != "1" && pass != "2"){
//      pass = "";
//    } 
    else if(pass != ""){
      if(pass == "11")
        pass = "1";
      else if(pass == "22")
        pass = "2";
    }else
      pass = "";
//    Serial.println("pass = " + pass);
    PT_DELAY(pt, 1, ts);
  }
  PT_END(pt);
}

//PT_THREAD(taskPassIn(struct pt* pt)){
//  static uint32_t ts;
//  PT_BEGIN(pt);
//  while(1)
//  {
//    if(isPassLDR && !isPassLDK){
//      Serial.println("Pass 1 Human!");
//      isPassLDR = false;
//      isPassLDK = false;
//    }
//    PT_DELAY(pt, 1, ts);
//  }
//  PT_END(pt);
//}

//PT_THREAD(taskPassOut(struct pt* pt)){
//  static uint32_t ts;
//  PT_BEGIN(pt);
//  while(1)
//  {
//    if(isPassLDR && isPassLDK){
//      Serial.println("Pass 1 Human!");
//      isPassLDR = false;
//      isPassLDK = false;
//    }
//    PT_DELAY(pt, 1, ts);
//  }
//  PT_END(pt);v
//}

void sentData(int HUMAN, int IN, int OUT){
  Serial1.print(20 - HUMAN);
  Serial1.print(".");
  Serial1.print(IN);
  Serial1.print(".");
  Serial1.println(OUT);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(115200);
  sentData(0, 0, 0);

  PT_INIT(&pt_taskAvgLDR);
  PT_INIT(&pt_taskCheckLDR);
  PT_INIT(&pt_taskAvgLDK);
  PT_INIT(&pt_taskCheckLDK);
  PT_INIT(&pt_taskPassAll);

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(percent(analogRead(LDR), avg));

  taskAvgLDR(&pt_taskAvgLDR);
  taskCheckLDR(&pt_taskCheckLDR);
  taskAvgLDK(&pt_taskAvgLDK);
  taskCheckLDK(&pt_taskCheckLDK);
  taskPassAll(&pt_taskPassAll);
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



#include<pt.h>
#define PT_DELAY(pt, ms, ts) \
  ts = millis(); \
  PT_WAIT_WHILE(pt, millis()-ts < (ms));

#define Color_S0 2
#define Color_S1 3
#define Color_S2 8
#define Color_S3 9
#define Color_Out 12

const int UNKNOW = 0;
const int RED = 1;
const int GREEN = 2;
const int BLUE = 3;
int color =UNKNOW;

int R = 0, G = 0, B = 0;

struct pt pt_taskColor;

PT_THREAD(taskColor(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1){
    digitalWrite(Color_S2, LOW);
    digitalWrite(Color_S3, LOW);
    R = pulseIn(Color_Out, LOW);

    digitalWrite(Color_S2, HIGH);
    digitalWrite(Color_S3, HIGH);
    G = pulseIn(Color_Out, LOW);

    digitalWrite(Color_S2, LOW);
    digitalWrite(Color_S3, HIGH);
    B = pulseIn(Color_Out, LOW);
    
    checkColor(R, G, B);
    if(color == BLUE)
    {
      PT_DELAY(pt, 10000, ts);
    }
    else
    {
      PT_DELAY(pt, 100, ts);
    }
  }
  PT_END(pt);
}

void checkColor(int R, int G, int B)
{

    if(R < 35 && G < 35 && B < 35)
    {
      Serial.print("R : ");
      Serial.print(R);
      Serial.print(" G : ");
      Serial.print(G);
      Serial.print(" B : ");
      Serial.print(B);
  
      Serial.println(" Unknow");
      
      color = UNKNOW;
    }
    else if(R < G && R < B)
    {
      Serial.print("R : ");
      Serial.print(R);
      Serial.print(" G : ");
      Serial.print(G);
      Serial.print(" B : ");
      Serial.print(B);
  
      Serial.println(" Red");
      color = RED;
    }
    else if(G < R && G < B)
    {
      Serial.print("R : ");
      Serial.print(R);
      Serial.print(" G : ");
      Serial.print(G);
      Serial.print(" B : ");
      Serial.print(B);
      
      Serial.println("  Green");
      color = GREEN;
    }
    else if(B < R && B < G)
    {
      Serial.print("R : ");
      Serial.print(R);
      Serial.print(" G : ");
      Serial.print(G);
      Serial.print(" B : ");
      Serial.print(B);
  
      Serial.println(" Blue");
      color = BLUE;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(Color_S0, OUTPUT);
  pinMode(Color_S1, OUTPUT);
  pinMode(Color_S2, OUTPUT);
  pinMode(Color_S3, OUTPUT);
  pinMode(Color_Out, INPUT);
  
  digitalWrite(Color_S0, HIGH); //set frequency to 20%
  digitalWrite(Color_S1, HIGH);
  
  PT_INIT(&pt_taskColor);
}

void loop() {
  // put your main code here, to run repeatedly:
  taskColor(&pt_taskColor);
//  Serial.print("R : ");
//  Serial.print(R);
//  Serial.print(" G : ");
//  Serial.print(G);
//  Serial.print(" B : ");
//  Serial.println(B);

}

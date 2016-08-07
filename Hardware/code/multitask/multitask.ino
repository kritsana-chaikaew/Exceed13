#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#include <pt.h>
#define PT_DELAY(pt, ms, ts) \
  ts = millis(); \
  PT_WAIT_WHILE(pt, millis()-ts < (ms));
#define LED1 11
#define LED2 12
#define LED3 13
#define LED4 14
#define knob A3
#define sw 2
struct pt pt_taskLED1;
struct pt pt_taskLED2;
struct pt pt_taskKnob;
struct pt pt_taskSwitch;
PT_THREAD(taskLED1(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1){
  digitalWrite(LED1, HIGH);
  PT_DELAY(pt, 1000, ts);
  digitalWrite(LED1, LOW);
  PT_DELAY(pt, 1000, ts);
  }
  PT_END(pt);
}
PT_THREAD(taskLED2(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1){
  digitalWrite(LED2, HIGH);
  PT_DELAY(pt, 500, ts);
  digitalWrite(LED2, LOW);
  PT_DELAY(pt, 500, ts);
  }
  PT_END(pt);
}

PT_THREAD(taskKnob(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1){
  lcd.print(analogRead(knob));
  PT_DELAY(pt, 500, ts);
  lcd.clear();
  }
  PT_END(pt);
}

PT_THREAD(taskSwitch(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1){
    if(digitalRead(sw) == 1)
    {
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      PT_DELAY(pt, 0, ts);
    }
    if(digitalRead(sw) == 0)
    {
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      PT_DELAY(pt, 0, ts);
    }
    PT_DELAY(pt, 500, ts);
  }
  PT_END(pt);
}

void setup() 
{
  lcd.begin(16, 2);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(sw, INPUT);
  PT_INIT(&pt_taskLED1);
  PT_INIT(&pt_taskLED2);
  PT_INIT(&pt_taskSwitch);
  PT_INIT(&pt_taskKnob);
}
void loop()
{
  taskLED1(&pt_taskLED1);
  taskLED2(&pt_taskLED2);
  taskKnob(&pt_taskKnob);
  taskSwitch(&pt_taskSwitch);
  
  
  
  ///int a = analogRead(knob);
  ///int b = digitalRead(sw);
  ///lcd.print(a);
  ///lcd.setCursor(0,1);
  ///lcd.print(b);
  ///delay(500);
  ///lcd.clear();
  
}


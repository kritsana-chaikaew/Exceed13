#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
char text[] = "Hello World";
char tmp;
void setup() {
 lcd.begin(16, 2);
}
void loop() {
 int i =0;
 tmp = text[1]
 for(i=0;i<11;i++){
  text[i] = text[i+1];
 }
 text[10] = 1;
 lcd.print(text[]);
 delay("1000")
}

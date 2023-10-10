#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int num = 0l;
void setup() {
  // put your setup code here, to run once:
  lcd.init();    
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  lcd.clear();
}

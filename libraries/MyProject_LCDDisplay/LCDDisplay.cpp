#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(int address, int columns, int rows) 
  : lcd(address, columns, rows) {
}

void LCDDisplay::initialize() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Water Level:");
}

// 显示水位过低警告
void LCDDisplay::showWaterLowWarning() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Level Low!");
  lcd.setCursor(0, 1);
  lcd.print("Auto Refill...");
}

// 显示正在补充水中
void LCDDisplay::showWateringInProgress() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Watering...");
  lcd.setCursor(0, 1);
  lcd.print("Please Wait...");
}

// 显示正常水位
void LCDDisplay::showWaterLevel(float waterHeight, int waterPercentage) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water: ");
  lcd.print(waterHeight, 1);
  lcd.print("cm");
  
  lcd.setCursor(0, 1);
  lcd.print("Level: ");
  lcd.print(waterPercentage);
  lcd.print("%");
}
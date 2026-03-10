#ifndef LCDDisplay_h
#define LCDDisplay_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LCDDisplay {
  private:
    LiquidCrystal_I2C lcd;
    
  public:
    LCDDisplay(int address, int columns, int rows);
    void initialize();
    void showWaterLevel(float height, int percentage); // 修改为显示水位高度和百分比
    void showWaterLowWarning();
    void showWateringInProgress();    
  };

#endif
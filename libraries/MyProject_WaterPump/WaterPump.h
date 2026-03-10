#ifndef WaterPump_h
#define WaterPump_h

#include <Arduino.h>

class WaterPump {
  private:
    int relayPin;
    int waterTime;
    int waterCount;
    bool isPumping;

  public:
    // 构造函数
    WaterPump(int pin, int time = 5000, int count = 3);
    
    // 初始化函数
    void begin();
    
    // 执行抽水操作
    void startWatering();
    
    // 检查是否正在抽水
    bool isWatering();
    
    // 停止抽水
    void stopWatering();
};

#endif
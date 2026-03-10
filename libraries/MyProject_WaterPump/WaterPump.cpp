#include "WaterPump.h"

// 构造函数
WaterPump::WaterPump(int pin, int time, int count) {
  relayPin = pin;
  waterTime = time;
  waterCount = count;
  isPumping = false;
}

// 初始化函数
void WaterPump::begin() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // 初始状态关闭继电器（低电平）
}

// 执行抽水操作
void WaterPump::startWatering() {
  if (isPumping) return;
  
  isPumping = true;
  
  // 执行抽水循环
  for(int i = 0; i < waterCount; i++) {
    digitalWrite(relayPin, HIGH); // 开始抽水（高电平）
    delay(waterTime);
    digitalWrite(relayPin, LOW); // 停止抽水（低电平）
    delay(waterTime);
  }
  
  // 抽水完成后，保持继电器关闭状态（低电平）
  digitalWrite(relayPin, LOW);
  isPumping = false;
}

// 检查是否正在抽水
bool WaterPump::isWatering() {
  return isPumping;
}

// 停止抽水
void WaterPump::stopWatering() {
  digitalWrite(relayPin, LOW); // 确保继电器关闭（低电平）
  isPumping = false;
}
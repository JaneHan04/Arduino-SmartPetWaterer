#include "UltrasonicSensor.h" //超声波测距
#include "LCDDisplay.h" //LCD显示
#include "WaterPump.h" //继电器控制水泵

//引脚
//超声波测距
#define TRIGGER_PIN 2
#define ECHO_PIN 3
//LCD
#define LCD_SDA A4
#define LCD_SCL A5
//继电器
#define WATERPUMP_PIN 9  


#define MAX_DISTANCE 50 //测量最大距离


// 关键参数
const float SENSOR_TO_BOTTOM = 13.9;   //超声波检测器到水碗底部高度
const float BOTTLE_HEIGHT = 4.0;  //水碗水位线的最高高度
const float WUCHA1 = 0.3;  //误差
const int LOW_WATER_THRESHOLD = 50; //水位低于50%就开启水泵
const int REQUIRED_CONSECUTIVE_READINGS = 10; //触发抽水的 “连续低水位次数”（防止单次误检测）

// 创建对象
UltrasonicSensor mySensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
LCDDisplay myDisplay(0x27, 16, 2);
WaterPump waterPump(WATERPUMP_PIN, 5000, 3); // 抽水5秒，重复3次

// 状态变量
int lowWaterCounter = 0;
bool isPumping = false; // 改为跟踪当前是否正在抽水

void setup() {
  Serial.begin(115200);
  Serial.println("水位检测器启动...");
  
  myDisplay.initialize();
  waterPump.begin();
  
  delay(1000);
}

void loop() {
  // 如果正在抽水，不进行水位检测
  if (waterPump.isWatering()) {
    return;
  }
  
  // 获取传感器到水面的距离
  float sensorToWater = mySensor.getDistance();
  
  // 计算实际水位高度
  float waterHeight = 0;
  if(sensorToWater > 0 && sensorToWater <= SENSOR_TO_BOTTOM) {
    waterHeight = SENSOR_TO_BOTTOM - sensorToWater;
  }
  
  // 计算水量百分比
  int waterPercentage = 0;
  if(waterHeight > 0) {
    waterPercentage = (waterHeight / BOTTLE_HEIGHT) * 100;
    waterPercentage = constrain(waterPercentage, 0, 100);
  }
  
  // 串口输出
  Serial.print("传感器到水面: ");
  Serial.print(sensorToWater, 1);
  Serial.print("cm, 水位高度: ");
  Serial.print(waterHeight, 1);
  Serial.print(" cm, 水量: ");
  Serial.print(waterPercentage);
  Serial.print("%, 连续低水位计数: ");
  Serial.print(lowWaterCounter);
  Serial.print("/");
  Serial.println(REQUIRED_CONSECUTIVE_READINGS);
  
  // 检查是否需要抽水
  if(waterPercentage < LOW_WATER_THRESHOLD) {
    lowWaterCounter++;
    
    // 连续10次检测到低水位就抽水
    if(lowWaterCounter >= REQUIRED_CONSECUTIVE_READINGS) {
      // 显示水位过低警告3秒
      myDisplay.showWaterLowWarning();
      Serial.println("!!! 警告：连续10次检测到水位过低 !!!");
      delay(3000);
      
      // 显示正在补充水中
      myDisplay.showWateringInProgress();
      Serial.println("开始抽水...");
      
      // 开始抽水
      waterPump.startWatering();
      
      // 重置计数器，允许下次再次抽水
      lowWaterCounter = 0;
      
      Serial.println("抽水完成");

      // 抽水完成后重新初始化LCD，防止乱码
      myDisplay.initialize();
      delay(1000); // 短暂延迟确保LCD稳定
    }
  } else {
    // 水位正常，重置计数器
    lowWaterCounter = 0;
  }
  
  // 正常显示水位
  myDisplay.showWaterLevel(waterHeight, waterPercentage);
  
  delay(1000);
}

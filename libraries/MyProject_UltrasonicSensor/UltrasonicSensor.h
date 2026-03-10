#ifndef UltrasonicSensor_h
#define UltrasonicSensor_h

#include <NewPing.h>

class UltrasonicSensor {
  private:
    NewPing sonar;
    
  public:
    UltrasonicSensor(int triggerPin, int echoPin, int maxDistance);
    float getDistance(); // 改为返回浮点数以提高精度
};

#endif
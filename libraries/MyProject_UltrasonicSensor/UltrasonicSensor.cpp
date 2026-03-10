#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin, int maxDistance) 
  : sonar(triggerPin, echoPin, maxDistance) {
}

float UltrasonicSensor::getDistance() {
  unsigned int uS = sonar.ping();
  float distance = uS / (US_ROUNDTRIP_CM * 1.0);
  
  // 只返回有效范围内的距离
  if(distance > 0 && distance < 50) {
    return distance;
  } else {
    return 0;
  }
}
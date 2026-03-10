//抽水
int relayPin = 9; //定义继电器的控制口
int water_time = 5000; //抽水时长
int water_count = 3; //抽水次数

void setup() {
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // 执行3次抽水循环
  for(int i = 0; i < water_count; i++) {
    digitalWrite(relayPin, HIGH); //开始抽水
    delay(water_time);
    digitalWrite(relayPin, LOW); //停止抽水
    delay(water_time);
  }
  

  // 停止程序执行，防止继续循环
  while(true) {
    // 空循环，什么也不做
  }
}

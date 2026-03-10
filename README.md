# 基于Arduino的智能宠物喂水系统

## 📌 项目简介

本项目设计并实现了一款基于 **Arduino UNO** 的智能宠物喂水系统。系统通过 **超声波传感器** 实时监测宠物水碗中的水位，并在水位过低时自动启动水泵补水，同时通过 **LCD显示屏** 向用户展示水位状态和系统提示。系统采用模块化设计，代码结构清晰，适合学习Arduino开发、传感器应用和自动控制原理。

------

## ✨ 功能特性

- **实时水位监测**：HC-SR04超声波传感器非接触式测量水位高度，精度可达±0.5cm。
- **智能补水控制**：当水位连续10次检测低于设定阈值（默认50%）时，自动启动水泵进行补水（工作5秒，停5秒，重复3次）。
- **LCD状态显示**：16x2 I2C LCD显示屏，实时显示水位高度（cm）和水百分比，以及低水位警告和补水过程提示。
- **防误触发机制**：连续多次检测才触发补水，避免因水面波动或偶发误差导致误动作。
- **模块化代码**：将超声波、LCD、水泵控制分别封装为类，便于复用和维护。

------

## 🧰 硬件需求

| 组件                 | 数量 | 说明               |
| :------------------- | :--- | :----------------- |
| Arduino UNO 开发板   | 1    | 主控芯片           |
| HC-SR04 超声波传感器 | 1    | 用于水位测量       |
| LCD1602 I2C显示屏    | 1    | 显示水位及系统状态 |
| 继电器模块           | 1    | 控制水泵           |
| 5V 直流潜水泵        | 1    | 抽水执行器         |
| 杜邦线、电源等       | 若干 | 连接电路           |

> **注意**：实际水位检测需要将超声波传感器固定在水碗上方，并测量传感器到底部的距离（`SENSOR_TO_BOTTOM`）和水碗高度（`BOTTLE_HEIGHT`），这些参数需根据实际结构在代码中调整。

------

## 📁 软件架构

项目采用面向对象方式组织代码，主要模块如下：

- **`MyProject_Main/main/main.ino`**：主程序，包含初始化、主循环和状态机逻辑。
- **`MyProject_UltrasonicSensor`** 库：封装超声波测距，提供`getDistance()`返回浮点数距离（cm）。
- **`MyProject_LCDDisplay`** 库：封装I2C LCD操作，提供不同显示界面（正常水位、低水位警告、补水过程）。
- **`MyProject_WaterPump`** 库：封装继电器控制水泵，提供开始补水、停止补水、是否正在补水等接口。

### 文件结构与放置说明

text

```
SmartPetWaterer/
├── README.md                     # 项目说明文档
├── MyProject_Main/               # 主程序文件夹
│   └── main/
│       └── main.ino              # 主程序入口
├── libraries/                    # 自定义库文件夹（需复制到 Arduino 库目录）
│   ├── MyProject_LCDDisplay/
│   │   ├── LCDDisplay.h
│   │   └── LCDDisplay.cpp
│   ├── MyProject_UltrasonicSensor/
│   │   ├── UltrasonicSensor.h
│   │   └── UltrasonicSensor.cpp
│   └── MyProject_WaterPump/
│       ├── WaterPump.h
│       └── WaterPump.cpp
└── tests/                        # 可选：独立测试程序
    └── water_test/water_test.ino
```



> **重要**：使用时，请将 `MyProject_LCDDisplay`、`MyProject_UltrasonicSensor`、`MyProject_WaterPump` 三个文件夹复制到 Arduino 的 `libraries` 目录下（通常位于 `文档/Arduino/libraries`），否则主程序无法找到这些自定义库。

------

## 🚀 快速开始

### 1. 硬件连接

| 组件         | 引脚       | Arduino 引脚 |
| :----------- | :--------- | :----------- |
| HC-SR04 TRIG | TRIG       | 2            |
| HC-SR04 ECHO | ECHO       | 3            |
| LCD I2C      | SDA        | A4           |
|              | SCL        | A5           |
| 继电器模块   | IN（控制） | 9            |
| 水泵         | 继电器输出 | 独立供电     |

### 2. 安装依赖库

- **NewPing**：用于超声波测距（可通过库管理器安装）。
- **LiquidCrystal_I2C**：用于I2C LCD（可通过库管理器安装，或手动安装）。

### 3. 放置自定义库

将本项目中的 `libraries` 文件夹下的三个子文件夹（`MyProject_LCDDisplay`、`MyProject_UltrasonicSensor`、`MyProject_WaterPump`）复制到 Arduino 的库目录：

- Windows: `C:\Users\用户名\Documents\Arduino\libraries\`
- macOS: `~/Documents/Arduino/libraries/`
- Linux: `~/Arduino/libraries/`

### 4. 打开并上传主程序

- 使用 Arduino IDE 打开 `MyProject_Main/main/main.ino`。

- 根据实际容器尺寸修改代码开头的参数：

	cpp

	```
	const float SENSOR_TO_BOTTOM = 13.9;   // 传感器到碗底距离 (cm)
	const float BOTTLE_HEIGHT = 4.0;       // 碗的有效高度 (cm)
	const int LOW_WATER_THRESHOLD = 50;    // 低水位阈值（百分比）
	```

- 选择开发板（Arduino UNO）和端口，点击上传。

### 5. 观察运行

上传成功后，打开串口监视器（波特率115200）可看到距离和水位信息。LCD会显示当前水位。当水位低于阈值且连续检测10次后，系统自动开始补水循环，LCD显示“Watering...”。

---

## 📝 自定义修改指南

- **调整补水逻辑**：修改`WaterPump`构造函数中的`waterTime`（抽水时长ms）和`waterCount`（循环次数）即可。
- **修改检测频率**：主循环中的`delay(1000)`为每秒检测一次，可根据需要调整。
- **更改LCD地址**：如果LCD地址不是`0x27`，可在`main.ino`中`LCDDisplay myDisplay(0x27, 16, 2);`修改
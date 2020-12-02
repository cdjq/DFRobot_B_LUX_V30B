# DFRobot_B_LUX_V30B
这是一个获取光照强度的传感器，IIC地址不可改变，可以通过IIC，，IIC地址不可改变，它有下面这些功能：

 * 向寄存器0x04里写入配置，设置不同的采集精度
 * 从寄存器0x00~0x03里读出光照强度数据


## 产品链接（链接到英文商城）
    SKU：产品名称

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary



## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
    /**
   * @brief 构造函数
   * @param cEN 传感器片选引脚
   * @param scl 传感器时钟线，默认指定为SCL
   * @param sda 传感器数据线，默认指定为SDA
   */
  DFRobot_B_LUX_V30B(uint8_t cEN, uint8_t scl = SCL, uint8_t sda = SDA);
/**
   * @brief 析构函数
   */
  ~DFRobot_B_LUX_V30B(){
  };
  /**
   * @brief 初始化函数
   */
  void begin(void);
  /**
   * @brief 获取光照强度
   * @return 获取的光照强度值
   */
  uint32_t lightStrengthLux(void);
  /**
   * @brief 设置寄存器模式
   * @param mode 需要配置的模式
   */
  void setMode(uint8_t mode);
  /**
   * @brief 获取寄存器模式
   * @return 配置的模式
   */
  uint8_t readMode(void);
```

## Compatibility

| MCU           | Work Well | Work Wrong | Untested | Remarks |
| ------------- | :-------: | :--------: | :------: | ------- |
| Arduino uno   |     √     |            |          |         |
| Mega2560      |           |            |          |         |
| Leonardo      |           |            |          |         |
| mPython/ESP32 |           |            |          |         |
| micro:bit     |           |            |          |         |


## History

- data 2020-12-02
- version V1.0


## Credits

Written by Alexander(fary_young@outlookcom), 2020. (Welcome to our [website](https://www.dfrobot.com/))
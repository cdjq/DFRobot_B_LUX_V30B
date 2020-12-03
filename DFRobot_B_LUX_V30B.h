/*!
 * @file DFRobot_B_LUX_V30B.h
 * @brief 定义DFRobot_B_LUX_V30B类
 * @n 这是一个获取光照强度的传感器，IIC地址不可改变，可以通过IIC，，IIC地址不可改变，它有下面这些功能
 * @n 向寄存器0x04里写入配置，设置不同的采集精度
 * @n 从寄存器0x00~0x03里读出光照强度数据
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Fary](Fary.young@outlook.com)
 * @version  V2.0
 * @date  2020-12-03
 * @https://github.com/fary99/DFRobot_B_LUX_V30B
 */
#ifndef  _DFROBOT_B_LUX_V30B_H_
#define  _DFROBOT_B_LUX_V30B_H_

#include <Arduino.h>

//使能调试宏函数
#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...)  {\
                  Serial.print("[");\
                  Serial.print(__FUNCTION__);\
                  Serial.print("(): ");\
                  Serial.print(__LINE__);\
                  Serial.print(" ] ");\
                  Serial.println(__VA_ARGS__);\
                  }
#else
#define DBG(...)
#endif

#define DFRobot_B_LUX_V30_IIC_Addr  0x94   //传感器IIC写地址

#define DFRobot_B_LUX_V30_DataReg        0x00   //光照值存储寄存器地址
#define DFRobot_B_LUX_V30_ConfigReg      0x04   //配置寄存器地址
typedef unsigned int    uint;
class DFRobot_B_LUX_V30B{
public:
  #define ACK        0x00
  #define NACK       0x01
  
  /*
   这里从数据手册上抄写关于这个寄存器的描述
     * ------------------------------------------------------------------------------------------
     * |    b7    |    b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
     * ------------------------------------------------------------------------------------------
     * |    0     |  MANUAL  |    0     |     0    |    CDR   |               TIM               |
     * ------------------------------------------------------------------------------------------
     *MANUAL  ：手动配置寄存器。0代表默认自动模式，在这种模式下，CDR，TIM[2:0]位被自动分配，光照值采集由 IC 的内部电路自动量程。
     *                        1代表配置手动模式，在这种模式下，CDR 和 TIM[2:0]位可以由用户设定
     *CDR     ：分流比寄存器。  0代表默认不划分，所有光电二极管的电流的推移到 ADC
     *                        1代表由 8 划分，只要光电二极管的电流的 1/8 变到 ADC。此模式是用于在高亮度的情况。
     *TIM[2:0]：积分时间 。
     *        ---------------------------------------------------------
     *          TIM[2:0]  |  时间（ms）  |  参数说明                  |
     *        ---------------------------------------------------------
     *             000    |      800     |   在微光环境下首选模式     |
     *        ---------------------------------------------------------
     *             001    |      400     |   ---                      |
     *        ---------------------------------------------------------
     *             010    |      200     |   ---                      |
     *        ---------------------------------------------------------
     *             011    |      100     |   在强光环境下优先选取模式 |
     *        ---------------------------------------------------------
     *             100    |      50      |   只有手动模式             |
     *        ---------------------------------------------------------
     *             101    |      250     |   只有手动模式             |
     *        ---------------------------------------------------------
     *             110    |      12.5    |   只有手动模式             |
     *        ---------------------------------------------------------
     *             111    |      6.25    |   只有手动模式             |
     *        ---------------------------------------------------------
     *手动模式设置精度：
     *     --------------------------------------------------------------------------------------
     *     |                          光照条件                          |  积分时间和分流比     |
     *     --------------------------------------------------------------------------------------
     *     |   最小精度    |   最大精度   |   最大值   |  采集时间(ms)  |    TIM     |     CDR  |
     *     —-------------------------------------------------------------------------------------
     *        0.054             11.52         2938          800              000             0   
     *        0.09              23.04         5875          400              001             0   
     *        0.18              46.08         11750         200              010             0   
     *        0.36              92.16         23501         100              011             0   
     *        0.36              92.16         23501         800              000             1   
     *        0.72              184.32        47002         50               100             0   
     *        0.72              184.32        47002         400              001             1   
     *        1.44              368.64        94003         25               101             0   
     *        1.44              368.64        94003         200              010             1   
     *        2.88              737.28        200000        12.5             110             0   
     *        2.88              737.28        200000        100              011             1   
     *        5.76              737.28        200000        6.25             111             0   
     *        5.76              737.28        200000        50               100             1   
     *        11.52             737.28        200000        25               101             1   
     *        23.04             737.28        200000        12.5             110             1   
     *        46.08             737.28        200000        6.25             111             1   
     *     —-------------------------------------------------------------------------------------
  
  */
  typedef struct {
    uint8_t TIM :3;   
    uint8_t CDR :1;
    uint8_t BIT_4 :1;
    uint8_t BIT_5 :1;
    uint8_t MANUAL :1;  
    uint8_t BIT_7 :1;
  }__attribute__((packed)) sLightConfig_t;
  typedef enum{
    eAutomatic = 0<<6,
    eManual = 1<<6,
  }eManualMode_t;
  typedef enum{
    eCDR_0 = 0<<3,
    eCDR_1 = 1<<3,
  }eCDRMode_t;
  typedef enum{
    eTime800ms = 0,
    eTime400ms = 1,
    eTime200ms = 2,
    eTime100ms = 3,
    eTime50ms = 4,
    eTime25ms = 5,
    eTime12_5ms = 6,
    eTime6_25ms = 7,
  }eTimeMode_t;

public:
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
   * @return 成功返回获取的光照强度值，失败返回-1
   */
  float lightStrengthLux(void);
  /**
   * @brief 设置寄存器模式
   * @param mode 需要配置的模式
   */
  uint8_t setMode(uint8_t isManualMode=0,uint8_t isCDR=0,uint8_t isTime=0);
  /**
   * @brief 获取寄存器模式
   * @return 配置的模式
   */
  uint8_t readMode(void);
private:
  /**
   * @brief IIC开始信号
   */
  void iicStartBit(void);
  /**
   * @brief IIC停止信号
   */
  void iicStopBit(void);
  /**
   * @brief IIC 主机发送一个应答
   * @return 当前周期SDA的值
   */
  void iicSendAck(uint8_t ack);
  /**
   * @brief IIC 主机接收一个应答
   * @return 当前周期SDA的值
   */
  uint8_t iicRecvAck(void);
  /**
   * @brief 发送一字节数据
   * @param data 需要发送的数据，可以是寄存器地址也可以是数据
   * @return 应答
   */
  uint8_t iicSend(uint8_t data);
  /**
   * @brief 接收一字节数据
   * @return 应答 返回0：ACK ，返回1：NACK
   */
  uint8_t iicReadByte();

  /**
   * @brief 进行读操作
   * @param num 要读的寄存器个数
   * @param *data 接收数据的地址
   */
  uint8_t iicRead(uint8_t num, uint8_t* data);

private:
  uint8_t _SDA;
  uint8_t _SCL;
  uint8_t _cEN;
  uint8_t _deviceAddr;
};
#endif





















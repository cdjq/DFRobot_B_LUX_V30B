/*!
 * @file B_LUX_V30B_Test.ino
 * @brief 设置寄存器模式以及读取光照值
 * @n 实验现象：传感器设备启动成功后一秒钟读取一次光照值
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Fary](fary_young@outlook.com)
 * @version  V1.0
 * @date  2020-12-03
 * @https://github.com/cdjq/DFRobot_B_LUX_V30B
 */
#include <DFRobot_B_LUX_V30B.h>
DFRobot_B_LUX_V30B    myLux(13);//传感器片选设置为13引脚，SCL、SDA采用默认配置
  /* 
   * MANUAL寄存器
   *   eAutomatic：默认自动配置寄存器,使用该模式后不必配置以下模式，IC自动配置。 
   *   eManual ：手动配置寄存器，配置该模式后与后面的模式组合使用
   * CDR寄存器
   *   eCDR_0：不划分分流比寄存器
   *   eCDR_1: 8划分分流比寄存器
   * TIM积分时间寄存器
   *   eTime800ms:采集时间800ms
   *   eTime400ms:采集时间400ms
   *   eTime200ms:采集时间200ms
   *   eTime100mse:采集时间100ms
   *   Time50ms:采集时间50ms
   *   eTime25ms:采集时间25ms
   *   eTime12_5ms:采集时间12.5ms
   *   eTime6_25ms:采集时间6.25ms
   * 手动模式组合（采集值不能超过各种模式的量程最大值）
   *   eManual+eCDR_0+eTime800ms    mode=64    采集最大值为：2938（lux）
   *   eManual+eCDR_0+eTime400ms    mode=65    采集最大值为：5875（lux）
   *   eManual+eCDR_0+eTime200ms    mode=66    采集最大值为：11750（lux）
   *   eManual+eCDR_0+eTime100ms    mode=67    采集最大值为：23501（lux）
   *   eManual+eCDR_0+eTime50ms     mode=68    采集最大值为：47002（lux）
   *   eManual+eCDR_0+eTime25ms     mode=69    采集最大值为：94003（lux）
   *   eManual+eCDR_0+eTime12.50ms  mode=70    采集最大值为：200000（lux）
   *   eManual+eCDR_0+eTime6.25ms   mode=71    采集最大值为：200000（lux）
   *   
   *   eManual+eCDR_1+eTime800ms    mode=72    采集最大值为：23501（lux）
   *   eManual+eCDR_1+eTime400ms    mode=73    采集最大值为：47002（lux）
   *   eManual+eCDR_1+eTime200ms    mode=74    采集最大值为：94003（lux）
   *   eManual+eCDR_1+eTime100ms    mode=75    采集最大值为：200000（lux）
   *   eManual+eCDR_1+eTime50ms     mode=76    采集最大值为：200000（lux）
   *   eManual+eCDR_1+eTime25ms     mode=77    采集最大值为：200000（lux）
   *   eManual+eCDR_1+eTime12.50ms  mode=78    采集最大值为：200000（lux）
   *   eManual+eCDR_1+eTime6.25ms   mode=79    采集最大值为：200000（lux）
   */
void setup() {
  Serial.begin(9600);
  myLux.begin();
  /* 
   * setmode与readMode可以省略，不配置时默认为上次使用时的配置
   * 使用setMode时需对其返回值进行判断，返回值为1即设置成功
   * while(!myLux.setMode(myLux.eManual,myLux.eCDR_0,myLux.eTime800ms));
   * Serial.print("mode: ");
   * Serial.println(myLux.readMode());
  */
}

void loop() {
  Serial.print("value: ");
  Serial.print(myLux.lightStrengthLux());
  Serial.println(" (lux).");
  delay(1000);
}

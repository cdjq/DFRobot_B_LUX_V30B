/*!
 * @file DFRobot_B_LUX_V30B.cpp
 * @brief 定义DFRobot_B_LUX_V30B类中方法的实现
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Fary](Fary.young@outlook.com)
 * @version  V1.0
 * @date  2020-12-02
 * @https://github.com/fary99/DFRobot_B_LUX_V30B
 */

#include <DFRobot_B_LUX_V30B.h>


DFRobot_B_LUX_V30B::DFRobot_B_LUX_V30B(uint8_t cEN, uint8_t scl, uint8_t sda)
{
  _deviceAddr = DFRobot_B_LUX_V30_IIC_Addr;
  _SCL = scl;
  _SDA = sda;
  _cEN = cEN;
}

void DFRobot_B_LUX_V30B::begin()
{
  pinMode(_SDA,OUTPUT);
  pinMode(_SCL,OUTPUT);
  pinMode(_cEN,OUTPUT);
  digitalWrite(_SCL,HIGH);
  digitalWrite(_SDA,HIGH);
  digitalWrite(_cEN,LOW);
  delay(1000);
  digitalWrite(_cEN,HIGH);
  
}
uint8_t DFRobot_B_LUX_V30B::readMode(void)
{
  uint8_t data;
  IIC_startBit();
  IIC_send(_deviceAddr);
  IIC_send(DFRobot_B_LUX_V30_ConfigReg);
  IIC_stopBit();
  IIC_read(1,&data);
  return data;
}
void DFRobot_B_LUX_V30B::setMode(uint8_t mode)
{
  uint8_t val;
  uint8_t data[6];
  IIC_startBit();
  IIC_send(_deviceAddr+0);
  IIC_send(DFRobot_B_LUX_V30_ConfigReg);
  IIC_send(mode);
  digitalWrite(_SDA,LOW);
  IIC_stopBit();
}
void DFRobot_B_LUX_V30B::IIC_startBit()
{
  uint cnt =0;
  digitalWrite(_SDA,LOW);
  for(cnt = 0; cnt < INTERVAL; cnt++){
    asm("nop");
  }
  digitalWrite(_SCL,LOW);
  for(cnt = 0; cnt < INTERVAL; cnt++){
    asm("nop");
  }
}

void DFRobot_B_LUX_V30B::IIC_stopBit()
{
  uint cnt =0;
  digitalWrite(_SCL,HIGH);
  for(cnt = 0; cnt < INTERVAL; cnt++){
    asm("nop");
  }
  digitalWrite(_SDA,HIGH);
  for(cnt = 0; cnt < INTERVAL; cnt++){
    asm("nop");
  }
}

uint8_t DFRobot_B_LUX_V30B::IIC_oneclock()
{
  uint8_t var=0;
  uint cnt =0;
  digitalWrite(_SCL,HIGH);
  for(cnt = 0; cnt < INTERVAL; cnt++){
    asm("nop");
  }
  var = digitalRead(_SDA);
  digitalWrite(_SCL,LOW);
  for(cnt = 0; cnt < INTERVAL; cnt++){
    asm("nop");
  }
  return var;
}
void DFRobot_B_LUX_V30B::IIC_write(uint8_t data)
{
  IIC_startBit();
  IIC_send(_deviceAddr);
  IIC_send(data);
  IIC_stopBit();
}

uint8_t DFRobot_B_LUX_V30B::IIC_send(uint8_t data)
{
  uint8_t result = 0;
  uint8_t cnt = 0;
  for(cnt = 0; cnt<8; cnt++){
    digitalWrite(_SDA,( data>>7 ));
    data <<= 1;
    IIC_oneclock();
  }
  
  pinMode(_SDA,INPUT);
  digitalWrite(_SDA,HIGH);
  result = IIC_oneclock();
  
  result = digitalRead(_SDA);
  
  digitalWrite(_SDA,HIGH);
  
  pinMode(_SDA,OUTPUT);
  
  return !result;
}

uint8_t DFRobot_B_LUX_V30B::IIC_read_byte(uint8_t ack, uint8_t* data)
{
  uint8_t result = 0;
  uint8_t cnt = 0;
  pinMode(_SDA,INPUT_PULLUP);
  for(cnt = 0; cnt < 8; cnt++){
    *data |= IIC_oneclock();
    if(cnt<7){
      *data <<= 1;
    }
  }
  digitalWrite(_SDA,ack);
  pinMode(_SDA,OUTPUT);
  result = IIC_oneclock();
  return !result;
}
void DFRobot_B_LUX_V30B::IIC_read(uint8_t num, uint8_t* data)
{
  uint8_t cnt;
  uint8_t addr =_deviceAddr | 0x01; 
  
  IIC_startBit();
  
  IIC_send(addr);
  
  delay(10);
  
  for(cnt = 0; cnt<(num - 1); cnt++){
    IIC_read_byte(ACK,&(data[cnt]));
  }
  IIC_read_byte(NACK,&(data[cnt]));
  IIC_stopBit();
}
uint32_t DFRobot_B_LUX_V30B::lightStrengthLux()
{
  
  uint32_t value = 0;
  uint8_t data[6];
  
  IIC_write(DFRobot_B_LUX_V30_DataReg);
  IIC_read(5,data);
  
  value = data[3];
  value = (value<<8)|data[2];
  value = (value<<8)|data[1];
  value = (value<<8)|data[0];
  return ((float)value*1.4) / 1000;
}

















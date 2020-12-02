#include <DFRobot_B_LUX_V30B.h>
DFRobot_B_LUX_V30B    myLux(13);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myLux.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  myLux.setMode(DFRobot_B_LUX_V30B::eManual+DFRobot_B_LUX_V30B::eCDR_0+DFRobot_B_LUX_V30B::eTime400ms);
  Serial.print("mode: ");
  Serial.println(myLux.readMode());
  Serial.print("value: ");
  Serial.println(myLux.lightStrengthLux());
  delay(1000);
}

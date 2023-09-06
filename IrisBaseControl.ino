//#include "IrisBase.h"

#define CMD_VEL_TIMEOUT 3000
#define SERIAL_BAUD 115200
#define SERIAL_RATE 10 

void setup() {
  // put your setup code here, to run once:


  //GPIO Pins for power supply of right encoder
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}

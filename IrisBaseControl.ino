//#include "IrisBase.h"
#include "IrisMotor.h"

#define CMD_VEL_TIMEOUT 3000
#define SERIAL_BAUD 115200
#define SERIAL_RATE 10 

unsigned long timer;

IrisMotor LeftMotor;
IrisMotor RightMotor;

void setup() {
  delay(1000);
  Serial.begin(SERIAL_BAUD);
  Serial.setTimeout(SERIAL_RATE);

  LeftMotor.init('L',2,3,4,10,11);
  RightMotor.init('R',5,6,7,13,12);


  //attachPCINT(digitalPinToPCINT(LeftMotor.ENC1Pin), LeftMotor.interruptListener, RISING);
  //attachPCINT(digitalPinToPCINT(RightMotor.ENC1PIn), RightMotor.interruptListener, RISING);


  //GPIO Pins for power supply of right encoder
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
}

void loop() {
  

  

}

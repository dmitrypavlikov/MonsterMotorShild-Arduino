//#include "IrisBase.h"
#include "IrisMotor.h"

#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>

#define CMD_VEL_TIMEOUT 3000
#define SERIAL_BAUD 115200
#define SERIAL_RATE 10 

unsigned long timer;

IrisMotor LeftMotor;
IrisMotor RightMotor;

void interruptListenerL() {
  LeftMotor.interruptListener();
}

void interruptListenerR() {
  RightMotor.interruptListener();
}

void setup() {
  delay(1000);
  Serial.begin(SERIAL_BAUD);
  Serial.setTimeout(SERIAL_RATE);

  LeftMotor.init('L',2,3,4,10,11);
  RightMotor.init('R',5,6,7,13,12);


  attachPCINT(digitalPinToPCINT(10), interruptListenerL, RISING);
  attachPCINT(digitalPinToPCINT(13), interruptListenerR, RISING);


  //GPIO Pins for power supply of right encoder
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);

  Serial.begin(115200);
}

void loop() {
  
  LeftMotor.tick();
  RightMotor.tick();

  if(millis() - timer > 50){
    timer = millis();
    LeftMotor.setGoalVelocity(0.2, 0.0);
    RightMotor.setGoalVelocity(0.2, 0.0);
    Serial.print(LeftMotor.getPresentVel());
    Serial.print(" ");
    Serial.println(RightMotor.getPresentVel());
    
  }
  

}

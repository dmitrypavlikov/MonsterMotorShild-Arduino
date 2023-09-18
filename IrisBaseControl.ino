#include "IrisBase.h"

#include <PinChangeInterrupt.h>
#include <PinChangeInterruptBoards.h>
#include <PinChangeInterruptPins.h>
#include <PinChangeInterruptSettings.h>

#define CMD_VEL_TIMEOUT 3000
#define SERIAL_BAUD 115200
#define SERIAL_RATE 10 

float GoalLinVel;
float GoalAngVel;;

unsigned long timer;
unsigned long serial_timer;

void interruptListenerL() {
  base.leftMotor.interruptListener();
}

void interruptListenerR() {
  base.rightMotor.interruptListener();
}

void setup() {
  delay(1000);
  Serial.begin(SERIAL_BAUD);
  Serial.setTimeout(SERIAL_RATE);

  base.init('L',2,3,4,10,11,
            'R',5,6,7,13,12);

  attachPCINT(digitalPinToPCINT(10), interruptListenerL, RISING);
  attachPCINT(digitalPinToPCINT(13), interruptListenerR, RISING);


  //GPIO Pins for power supply of right encoder
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);

  serial_timer = millis();
  timer = millis();
}

void loop() {
  base.tick();
  base.setGoalVelocity(GoalLinVel, GoalAngVel);
  
  if(millis() - timer > SERIAL_FREQ){
    Serial.print("pos,");
    Serial.print(base.getBasePosX());
    Serial.print(",");
    Serial.print(base.getBasePosY());
    Serial.print(",");
    Serial.print(base.getBasePosTh());
    Serial.print(",");
    Serial.print(base.getPresentLinVel());
    Serial.print(",");
    Serial.println(base.getPresentAngVel());
    

    timer = millis();
    
  }

  if(millis() - serial_timer > CMD_VEL_TIMEOUT){
    GoalLinVel = 0.0;
    GoalAngVel = 0.0;  
  }
  
}

void serialEvent() {
  char mail[12]={}; // [+x.xx,+x.xx/n] 12 chars
  String num;
  bool split = true;
  Serial.readBytesUntil('\n', mail, 12);

  for(int i=0; i<sizeof(mail); i++) {
    if(mail[i] != ',') {
      num += mail[i];
    } else {
      GoalLinVel = num.toFloat(); // Read linear velocity
      num = "";
      }
  }
    GoalAngVel = num.toFloat(); // Read angular velocity
    serial_timer = millis();
}

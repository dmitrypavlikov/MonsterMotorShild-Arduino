#ifndef IRIS_BASE_H
#define IRIS_BASE_H

#include"IrisMotor.h"
#include"IrisBaseConfig.h"

class IrisBase {
    private:
      double BasePosX;
      double BasePosY;
      double BasePosTh;

      unsigned long Timer;

      void calculateBasePos();
      double normalizeAngle(double angle);

    public:
      IrisMotor leftMotor;
      IrisMotor rightMotor;

      void init(int L_TPS, int L_CWPin, int L_CCWPin, 
                  int L_PWMPin, int L_ENC1Pin, int L_ENC2Pin,
                  int R_TPS, int R_CWPin, int R_CCWPin,
                  int R_PWMPin, int R_ENC1Pin, int R_ENC2Pin);

      void tick();

      /* Getters */
      double getPresentVelL();
      double getPresentVelR();
      double getPresentVelX();
      double getPresentVelTh();
      double getBasePosX();
      double getBasePosY();
      double getBasePosTh();
      
      /* Setters */
      void setGoalVelocity(double _GoalVelocityX, double _GoalVelocityTh);
};

extern IrisBase base; 

#endif

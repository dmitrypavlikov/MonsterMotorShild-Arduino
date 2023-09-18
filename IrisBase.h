#ifndef IRIS_BASE_H
#define IRIS_BASE_H

#include"IrisMotor.h"
#include"IrisBaseConfig.h"

class IrisBase {
    private:
      double GoalVelocityX;
      double GoalVelocityY;
		  double GoalVelocityTh;

		  double RealVelocityX;
		  double RealVelocityTh;

      double BasePosX;
      double BasePosY;
      double BasePosTh;

      unsigned long Timer;

      void calculateBasePos();

    public:
      IrisMotor leftMotor;
      IrisMotor rightMotor;

      void init(char L_LorR, int L_CWPin, int L_CCWPin, 
                  int L_PWMPin, int L_ENC1Pin, int L_ENC2Pin,
                  char R_LorR, int R_CWPin, int R_CCWPin,
                  int R_PWMPin, int R_ENC1Pin, int R_ENC2Pin);

      void tick();

      
      void setGoalVelocity(double _GoalVelocityX, double _GoalVelocityTh);

      double getPresentVelL();
      double getPresentVelR();
      double getPresentLinVel();
      double getPresentAngVel();
      double getBasePosX();
      double getBasePosY();
      double getBasePosTh();


};

extern IrisBase base; 

#endif

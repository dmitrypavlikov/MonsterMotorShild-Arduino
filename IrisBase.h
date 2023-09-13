#ifndef IRIS_BASE_H
#define IRIS_BASE_H

#include"IrisMotor.h"
#include"IrisBaseConfig.h"

class IrisBase {
    private:
      double GoalVelocityX;
      double GoalVelocityY;
		  double GoalVelocityW;

		  double RealVelocityX;
		  double RealVelocityY;
		  double RealVelocityW;

      double BasePosX;
      double BasePosY;
      double BasePosW;

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

      
      void setGoalVelocity(double _GoalVelocityX, double _GoalVelocityW);

      double getPresentVelL();
      double getPresentVelR();
      double getPresentLinVel();
      double getPresentAngVel();
      double getBasePosX();
      double getBasePosY();
      double getBasePosW();


};

extern IrisBase base; 

#endif

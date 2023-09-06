#ifndef IRIS_MOTOR_H
#define IRIS_MOTOR_H

#include "IrisMotorConfig.h"
#include <Arduino.h>

class IrisMotor {
    private:
        // 'L' or 'l' if left motor, 'R' or 'r' if right motor
        // It's important for TIX_PER_SPIN of encoders
        char LorR;
        int CWPin, CCWPin, PWMPin, ENC1Pin, ENC2Pin;
        int PWM;
        int PresEncoderPose;    //
        int PastEncoderPose;    //
        int GoalEncoderPose;    //
        double PresEncoderVel;  //
        double PastEncoderVel;  //
        double IntegralVel;     // VelocityPID
        double IntegralPos;     // PosityonPID

        double GoalLinVel;      // Задают извне
        double GoalAngVel;      // Задают извне
        
        bool FlagInterrupt;     // InterruptListener()
        bool FlagSavePosition;  // CalcVelocity()

        unsigned long Timer;    // millis()

        void calcVelocity();    // Main calculation
        void controlDriver();   // 
        void velocityPID();     // PID for moving
        void positionPID();     // PID for standing


    public:
        void init(char LorR, int CWPin, int CCWPin, int PWMPin, int ENC1Pin, int ENC2Pin);
        void interruptListener();
        void tick();

        // TODO getters!
        double getPresentVel();

        // TODO setters!
        void setGoalVelocity(double lin, double ang);




};

#endif;
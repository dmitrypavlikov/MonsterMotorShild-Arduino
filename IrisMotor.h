#ifndef IRIS_MOTOR_H
#define IRIS_MOTOR_H

#include "IrisMotorConfig.h"
#include <Arduino.h>

class IrisMotor {
    private:
        int TicksPerSpin;
        int CWPin, CCWPin, PWMPin, ENC1Pin, ENC2Pin;
        int PWM;
        int PresEncoderPose;    //
        int PastEncoderPose;    //
        int GoalEncoderPose;    //
        double PresEncoderVel;  //
        double PastEncoderVel;  //
        double GoalEncoderVel;
        
        double IntegralVel;     // VelocityPID
        double IntegralPos;     // PosityonPID

        bool FlagInterrupt;     // InterruptListener()
        bool FlagSavePosition;  // CalcVelocity()

        unsigned long Timer;    // millis()

        void calcVelocity();    // Main calculation
        void controlDriver();
        void velocityPID();     // PID for control velocity of wheel
        void positionPID();     // PID for save position
        void relaxMotor();      // Make motor no power


    public:
        void init(int TicksPerSpin, int CWPin, int CCWPin, int PWMPin, int ENC1Pin, int ENC2Pin);
        void interruptListener();
        void tick();
        
        /* Getters */
        double getPresentVel();

        /* Setters */
        void setGoalVelocity(double GoalVelocity);

};

#endif;

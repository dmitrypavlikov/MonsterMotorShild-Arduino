#ifndef IRIS_MOTOR_H
#define IRIS_MOTOR_H

// #include "IrisMotorConfig.h"
#include <Arduino.h>

class IrisMotor {
    private:
        char LorR;      // Left or Right motor flag

        int CWPin, CCWPin, PWMPin, ENC1Pin, ENC2Pin;    // Init
        int PWM;                                        // ControlDriver
        int PresEncoderPose, PastEncoderPose;           // Decoding of encoder
        int GoalEncoderPose;                    // NOT USED YET
        double PresEncoderVel, PastEncoderVel;          // PID
        
        double GoalLinVel;      // Задают извне
        double GoalAngVel;      // Задают извне
        double IntegralVel;     // VelocityPID
        double IntegralPos;     // PosityonPID


        bool FlagInterrupt;     // InterruptListener()
        bool FlagSavePosition;  // CalcVelocity()

        unsigned long Timer;    // millis()

        void calcVelocity();    // Yep 
        void controlDriver();   // Yep
        void velocityPID();     // In work
        void positionPID();     // NOT USED YET


    public:
        void init(char LorR, int CWPin, int CCWPin, int PWMPin, int ENC1Pin, int ENC2Pin);
        void interruptListener();
        void tick();

        // TODO getters!
        // float getPresent
        // TODO setters!
        // void setGoalVelocity(double goalVelocity);




};

#endif;
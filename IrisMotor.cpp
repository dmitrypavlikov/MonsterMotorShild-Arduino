#include "IrisMotor.h"

void IrisMotor::init(char _LorR, int _CWPin, int _CCWPin, int _PWMPin, int _ENC1Pin, int _ENC2Pin){
    // 'L' or 'l' if left motor, 'R' or 'r' if right motor
    // It's important for TIX_PER_SPIN of encoders
    LorR = _LorR;       
    CWPin = _CWPin;
    CCWPin = _CCWPin;
    PWMPin = _PWMPin;
    ENC1Pin = _ENC1Pin;
    ENC2Pin = _ENC2Pin;

    Timer = millis();

    PWM = 0;                // For speed control
    PresEncoderPose = 0;    // For encoder decoding
    PastEncoderPose = 0;    // For encoder decoding
    PresEncoderVel = 0.0;   // For err of PID
    PastEncoderVel = 0.0;   // For D part of PID
    IntegralVel = 0;        // For I part of PID
    IntegralPos = 0;        // For I part in PID
    
    FlagInterrupt = false;

    
    pinMode(CWPin, OUTPUT);
    pinMode(CWWPin, OUTPUT);
    pinMode(PWMPin, OUTPUT);
    pinMode(ENC1Pin, INPUT_PULLUP);
    pinMode(ENC2Pin, INPUT_PULLUP);

}

    void IrisMotor::calcVelocity() {
        if(millis() - Timer > ENCODER_FREQ){
            Timer = millis();
            PresEncoderVel = (PresEncoderPose - PastEncoderPose)*WHEEL_DIAMETER*3.14/ENCODER_FREQ;
            if((LorR == 'L')||(LorR == 'l')) {
                PresEncoderVel = PresEncoderVel/TIX_PER_SPIN_L;
            }
            if((LorR == 'R')||(LorR == 'r')) {
                PresEncoderVel = PresEncoderVel/TIX_PER_SPIN_R;
            }
            PastEncoderPose = PresEncoderPose;

            if(PresEncoderVel != 0.0) {
                velocityPID();
                controlDriver();
                FlagSavePosition = true;
            } else {
                if(FlagSavePosition) {
                    GoalEncoderPos = PresEncoderPose;
                    FlagSavePosition = false;
                }

                // Обнуления
                IntegralPos = 0;
                IntegralVel = 0;
                positionPID();
                controlDriver();


            }
        }
    }

    void IrisMotor::velocityPID() {
        if((LorR == 'L')||(LorR == 'l')) {
            double err = GoalLinVel - GoalAngVel*BASE_WIDTH - PresEncoderVel;
        }
        if((LorR == 'R')||(LorR == 'r')) {
            double err = GoalLinVel + GoalAngVel*BASE_WIDTH - PresEncoderVel;
        }
        IntegralVel += err*((double)ENCODER_FREQ/1000);
        double D = (PresEncoderVel - PastEncoderVel);
        PastEncoderVel = PresEncoderVel;
        PWM = round(err*V_KP + IntegralVel*V_KI + D*V_KD);
    }

    void IrisMotor::positionPID() {
        double err = GoalEncoderPos - PresEncoderPose;
        IntegralPos += err*((double)ENCODER_FREQ/1000);
        double D = (PresEncoderPose - PastEncoderPose);
        PastEncoderPose = PresEncoderPose;
        PWM = round(err*V_KP + IntegralPos*V_KI + D*V_KD);
    }


    

void IrisMotor::controlDriver() {
    if(PWM > 0.00) {
        digitalWrite(CWPin, HIGH);
        digitalWrite(CWWPin, LOW);
        analogWrite(PWMPin, abs(PWM))
    }
    if(PWM < 0.00) {
        digitalWrite(CWPin, LOW);
        digitalWrite(CCWPin, HIGH);
        analogWrite(PWMPin, abs(PWM))
    }

void IrisMotor::interruptListener() {
    FlagInterrupt = true;
}

void IrisMotor::tick() {
    if(FlagInterrupt){
        if(digitalRead(ENC2Pin)) {    
            PresEncoderPose++;
        } else {
            PresEncoderPose--;
        }
        
        FlagInterrupt = false;
    }

    calcVelocity();
}

}
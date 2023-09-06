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

    PWM = 0;                //
    PresEncoderPose = 0;    // For encoder decoding
    PastEncoderPose = 0;    // For encoder decoding
    GoalEncoderPose = 0;    // For PositionSave
    PresEncoderVel = 0.0;   //
    PastEncoderVel = 0.0;   //
    IntegralVel = 0.0;      //
    IntegralPos = 0.0;      //

    GoalLinVel = 0.0;       // Задаются извне
    GoalAngVel = 0.0;       // Задаются извне

    FlagInterrupt = false;      // in InterruptListener()
    FlagSavePosition = false;   // in CalcVelocity()
    
    Timer = millis(); 

    pinMode(CWPin, OUTPUT);
    pinMode(CCWPin, OUTPUT);
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
                GoalEncoderPose = PresEncoderPose;
                FlagSavePosition = false;
            }

            IntegralPos = 0;
            IntegralVel = 0;
            positionPID();
            controlDriver();
        }
    }
}

void IrisMotor::velocityPID() {
    double err = 0.0;
    if((LorR == 'L')||(LorR == 'l')) {
        err = GoalLinVel - GoalAngVel*BASE_WIDTH - PresEncoderVel;
    }
    if((LorR == 'R')||(LorR == 'r')) {
        err = GoalLinVel + GoalAngVel*BASE_WIDTH - PresEncoderVel;
    }
    IntegralVel += err*((double)ENCODER_FREQ/1000);
    double D = (PresEncoderVel - PastEncoderVel);
    PastEncoderVel = PresEncoderVel;
    PWM = constrain(round(err*V_KP + IntegralVel*V_KI + D*V_KD), MIN_PWM, MAX_PWM);
}

void IrisMotor::positionPID() {
    double err = GoalEncoderPose - PresEncoderPose;
    IntegralPos += err*((double)ENCODER_FREQ/1000);
    double D = (PresEncoderPose - PastEncoderPose);
    PastEncoderPose = PresEncoderPose;
    PWM = constrain(round(err*V_KP + IntegralPos*V_KI + D*V_KD), MIN_PWM, MAX_PWM);
}


    

void IrisMotor::controlDriver() {
    if(PWM > 0.00) {
        digitalWrite(CWPin, HIGH);
        digitalWrite(CCWPin, LOW);
        analogWrite(PWMPin, abs(PWM));
    }
    if(PWM < 0.00) {
        digitalWrite(CWPin, LOW);
        digitalWrite(CCWPin, HIGH);
        analogWrite(PWMPin, abs(PWM));
    }
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

void IrisMotor::setGoalVelocity(double lin, double ang){
    GoalLinVel = lin;
    GoalAngVel = ang;
}

double IrisMotor::getPresentVel(){
    return PresEncoderVel;
}

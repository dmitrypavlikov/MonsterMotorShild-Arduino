#include "IrisMotor.h"

void IrisMotor::init(int _TPS, int _CWPin, int _CCWPin, int _PWMPin, int _ENC1Pin, int _ENC2Pin){
    TicksPerSpin = _TPS;     
    CWPin = _CWPin;
    CCWPin = _CCWPin;
    PWMPin = _PWMPin;
    ENC1Pin = _ENC1Pin;
    ENC2Pin = _ENC2Pin;

    PWM = 0;          
    PresEncoderPose = 0;    // For encoder decoding
    PastEncoderPose = 0;    // For encoder decoding
    GoalEncoderPose = 0;    // For PositionSave
    PresEncoderVel = 0.0;   //
    PastEncoderVel = 0.0;   //
    GoalEncoderVel = 0.0;

    IntegralVel = 0.0;
    IntegralPos = 0.0;

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
    if(millis() - Timer > CYCLE_FREQ*1000){
        Timer = millis();
        PresEncoderVel = ((PresEncoderPose - PastEncoderPose)*WHEEL_DIAMETER*3.14)/(CYCLE_FREQ*TicksPerSpin);
        PastEncoderPose = PresEncoderPose;
        if(GoalEncoderVel != 0.0) {
            velocityPID();
            controlDriver();
            FlagSavePosition = true;
        } else {
            // SavePositionPID - Great option if floor inclined
            // Not used in Iris now
            
            /* if(FlagSavePosition) {
                GoalEncoderPose = PresEncoderPose;
                FlagSavePosition = false;
            }

            IntegralPos = 0;
            IntegralVel = 0;
            positionPID();
            controlDriver();}*/

            relaxMotor();
            IntegralVel = 0;
            IntegralPos = 0;
       }   
    }
}

void IrisMotor::velocityPID() {
    double err = 0.0;
    err = GoalEncoderVel - PresEncoderVel;
    IntegralVel += err*((double)CYCLE_FREQ);
    double D = (PresEncoderVel - PastEncoderVel);
    PastEncoderVel = PresEncoderVel;
    PWM = constrain(round(err*V_KP + IntegralVel*V_KI + D*V_KD), MIN_PWM, MAX_PWM);
}

void IrisMotor::positionPID() {
    double err = 0.0;
    err = GoalEncoderPose - PresEncoderPose;
    IntegralPos += err*((double)CYCLE_FREQ);
    double D = (PresEncoderPose - PastEncoderPose);
    PastEncoderPose = PresEncoderPose;
    PWM = constrain(round(err*P_KP + IntegralPos*P_KI + D*P_KD), MIN_PWM, MAX_PWM);
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

void IrisMotor::relaxMotor(){
  digitalWrite(CWPin, LOW);
  digitalWrite(CCWPin, LOW);
  PWM = 0;
  analogWrite(PWMPin, abs(PWM));
  
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

/* Getters */
double IrisMotor::getPresentVel(){
    return PresEncoderVel;
}

/* Setters */
void IrisMotor::setGoalVelocity(double GoalVelocity){
    GoalEncoderVel = GoalVelocity;
}

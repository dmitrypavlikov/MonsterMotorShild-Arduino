#include "IrisBase.h"

IrisBase Base = IrisBase();

void IrisBase::init(char L_LorR, int L_CWPin, int L_CCWPin, 
                    int L_PWMPin, int L_ENC1Pin, int L_ENC2Pin,
                    char R_LorR, int R_CWPin, int R_CCWPin,
                    int R_PWMPin, int R_ENC1Pin, int R_ENC2Pin) {

    LeftMotor.init(L_LorR, L_CWPin, L_CCWPin, 
                    L_PWMPin, L_ENC1Pin, L_ENC2Pin);
    RightMotor.init(R_LorR, R_CWPin, R_CCWPin,
                    R_PWMPin, R_ENC1Pin, R_ENC2Pin);
}

void IrisBase::tick() {
    LeftMotor.tick();
    RightMotor.tick();
}

void IrisBase::setGoalVelocity(double _GoalVelocityX, double _GoalVelocityW) {
    LeftMotor.setGoalVelocity(_GoalVelocityX, _GoalVelocityW);
    RightMotor.setGoalVelocity(_GoalVelocityX, _GoalVelocityW);
}

double IrisBase::getPresentVelL() {
    return LeftMotor.getPresentVel();
}

double IrisBase::getPresentVelR() {
    return RightMotor.getPresentVel();
}

double IrisBase::getPresentAngVel() {


}

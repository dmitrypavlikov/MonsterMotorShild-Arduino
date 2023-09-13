#include "IrisBase.h"

IrisBase base = IrisBase();

void IrisBase::init(char L_LorR, int L_CWPin, int L_CCWPin, 
                    int L_PWMPin, int L_ENC1Pin, int L_ENC2Pin,
                    char R_LorR, int R_CWPin, int R_CCWPin,
                    int R_PWMPin, int R_ENC1Pin, int R_ENC2Pin) {

    leftMotor.init(L_LorR, L_CWPin, L_CCWPin, 
                    L_PWMPin, L_ENC1Pin, L_ENC2Pin);
    rightMotor.init(R_LorR, R_CWPin, R_CCWPin,
                    R_PWMPin, R_ENC1Pin, R_ENC2Pin);

    GoalVelocityX = 0.0;
    GoalVelocityY = 0.0;
    GoalVelocityW = 0.0;

    RealVelocityX = 0.0;
    RealVelocityY = 0.0;
    RealVelocityW = 0.0;
    
    BasePosX = 0.0;
    BasePosY = 0.0;
    BasePosW = 0.0;

    Timer = millis();
}

void IrisBase::tick() {
    leftMotor.tick();
    rightMotor.tick();

    if(millis() - Timer > 50) {
        this->calculateBasePos();
        Timer = millis();
    }
}

void IrisBase::calculateBasePos() {
    double dx = 0;
    double dy = 0;

    dx = this->getPresentLinVel() * cos(BasePosW + this->getPresentAngVel()/2);
    dy = this->getPresentLinVel() * sin(BasePosW + this->getPresentAngVel()/2);

    BasePosX += dx;
    BasePosY += dy;
    BasePosW += this->getPresentAngVel();
}

void IrisBase::setGoalVelocity(double _GoalVelocityX, double _GoalVelocityW) {
    leftMotor.setGoalVelocity(_GoalVelocityX, _GoalVelocityW);
    rightMotor.setGoalVelocity(_GoalVelocityX, _GoalVelocityW);
}

double IrisBase::getPresentLinVel() {
    return (this->getPresentVelL() + this->getPresentVelR()) / 2;
}

double IrisBase::getPresentAngVel() {
    return (this->getPresentVelR() - this->getPresentVelL()) / BASE_WIDTH;
}

double IrisBase::getPresentVelL() {
    return this->leftMotor.getPresentVel();
}

double IrisBase::getPresentVelR() {
    return this->rightMotor.getPresentVel();
}

double IrisBase::getBasePosX() {
    return this->BasePosX;
}

double IrisBase::getBasePosY() {
    return this->BasePosY;
}

double IrisBase::getBasePosW() {
    return this->BasePosW;
}

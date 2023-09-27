#include "IrisBase.h"

IrisBase base = IrisBase();

void IrisBase::init(int L_TPS, int L_CWPin, int L_CCWPin, 
                    int L_PWMPin, int L_ENC1Pin, int L_ENC2Pin,
                    int R_TPS, int R_CWPin, int R_CCWPin,
                    int R_PWMPin, int R_ENC1Pin, int R_ENC2Pin) {

    leftMotor.init(L_TPS, L_CWPin, L_CCWPin, 
                    L_PWMPin, L_ENC1Pin, L_ENC2Pin);
    rightMotor.init(R_TPS, R_CWPin, R_CCWPin,
                    R_PWMPin, R_ENC1Pin, R_ENC2Pin);
    
    BasePosX = 0.0;
    BasePosY = 0.0;
    BasePosTh = 0.0;

    Timer = millis();
}

void IrisBase::tick() {
    leftMotor.tick();
    rightMotor.tick();

    if(millis() - Timer > CYCLE_FREQ*1000) {
        this->calculateBasePos();
        Timer = millis();
    }
}

void IrisBase::calculateBasePos() {
    double dx = 0;
    double dy = 0;

    double dS = this->getPresentVelX() * CYCLE_FREQ;
    double dTh = this->getPresentVelTh() * CYCLE_FREQ;

    dx = dS * cos(BasePosTh + dTh/2);
    dy = dS * sin(BasePosTh + dTh/2);

    BasePosX += dx;
    BasePosY += dy;
    BasePosTh += dTh;
}

double IrisBase::normalizeAngle(double angle){
    while(angle > pi){
        angle -= 2.0*pi;
    }
    while(angle < -pi){
        angle += 2.0*pi;
    }
    return angle;
}

/* Getters */
double IrisBase::getPresentVelX() {
    return (this->getPresentVelL() + this->getPresentVelR()) / 2;
}

double IrisBase::getPresentVelTh() {
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

double IrisBase::getBasePosTh() {
    return this->normalizeAngle(this->BasePosTh);
}

/* Setters */
void IrisBase::setGoalVelocity(double _GoalVelocityX, double _GoalVelocityTh) {
    leftMotor.setGoalVelocity(_GoalVelocityX - _GoalVelocityTh*BASE_WIDTH);
    rightMotor.setGoalVelocity(_GoalVelocityX + _GoalVelocityTh*BASE_WIDTH);
}

#ifndef IRIS_MOTOR_CONFIG_H
#define IRIS_MOTOR_CONFIG_H

    #define CYCLE_FREQ 0.05     // 20 Hz

    /*Physical parameters*/
    #define WHEEL_DIAMETER 0.2
    #define BASE_WIDTH 0.315
    #define MAX_PWM 150 // 250
    #define MIN_PWM -150 //-250

    /*VelocityPID koefficients*/
    #define V_KP 130//130
    #define V_KI 130//150
    #define V_KD 0
    
    /*PositionPID koefficients*/
    #define P_KP 3
    #define P_KI 0.1
    #define P_KD 0


#endif

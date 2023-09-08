#ifndef IRIS_MOTOR_CONFIG_H
#define IRIS_MOTOR_CONFIG_H

    #define ENCODER_FREQ 0.05     // 20 Hz
    #define TIX_PER_SPIN_L 496  
    #define TIX_PER_SPIN_R 696

    /*Physical parameters*/
    #define WHEEL_DIAMETER 0.2
    #define BASE_WIDTH 0.315
    #define MAX_PWM 250
    #define MIN_PWM -250

    /*PositionPID koefficients*/
    #define P_KP 3
    #define P_KI 0.1
    #define P_KD 0

    /*VelocityPID koefficients*/
    #define V_KP 350
    #define V_KI 60
    #define V_KD 0


#endif

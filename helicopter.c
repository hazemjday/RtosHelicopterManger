#include "helicopter.h"
#include <stdio.h>

/* 
 * Fonction: dataValidation...
 * Period = 1/180s 
 */
void dataValidation(void) {
    printf("*** dataValidation: Validate sensor data and select data source... ***\n" );
}

/* 
 * Fonction: keyboardDataTracking...
 * Period = 1/30s 
 */
void keyboardDataTracking(void) {
    printf("*** keyboardDataTracking: keyboard input + data normalization + tracking... ***\n" );
}

/* 
 * Fonction: controlOuterLoops...
 * Period = 1/30s 
 */
void controlOuterLoops(void) {
    printf("*** controlOuterLoops: control laws of the outer pitch-control loop, outer roll-control loop and outer yaw control loop... ***\n");
}

/* 
 * Fonction controlInnerLoops...
 * Period = 1/90s 
 */
void controlInnerLoops(void) {
    printf("*** controlInnerLoops: control laws of the inner pitch-control loop and inner yaw control loop... ***\n");
}

/* 
 * Fonction computeNComd...
 * Period = 1/180s 
 */
void computeNComd(void) {
    printf("*** computeNComd: Compute the control laws and output commands.... ***\n" );
}


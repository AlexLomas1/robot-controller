#include <stdio.h>
#include "pico/stdlib.h"

void driving_motor_setup() {
    // Sets up the driving motor.
    printf("Setting up driving motor...\n");
}

int driving_motor_stop() {
    // Sets speed of driving motor to 0, but does not shut down motor.
    printf("Setting motor speed to zero...\n");
    int new_speed = 0;
    return new_speed;
}

void driving_motor_shutdown() {
    // Shuts down driving motor. 
    driving_stop(); // is it okay that this function returns a value, but it is being treated
    // as a procedure?
    printf("Shutting down driving motor...\n");
}

int drive_forwards() {
    // Turns on the driving motor, with the motor speed value (0-255) initialised to 50.
    printf("Setting driving motor to ON\n");
    int new_speed = 50; // Placeholder value, set to whatever default speed is.
    return new_speed;
}

int accelerate(const int current_speed) {
    // Increases motor speed value (0-255) by 10 if possible. Otherwise, motor speed value
    // will be increased to maximum, or an error message will be printed if already at maximum
    // speed.
    int new_speed = current_speed;
    // Might be better to have constant to store the speed change intervals (e.g. at the
    // moment speed intervals is 10).
    if (current_speed == 255) {
        printf("Already at max speed!\n");
    }
    else if (current_speed + 10 >= 255) {
        // Increase motor speed to 255.
        new_speed = 255;
    }
    else {
        // Increase motor speed value by 5.
        new_speed += 10;
    }
    return new_speed;
}

int decelerate(const int current_speed) {
    // Decreases motor speed value (0-255) by 10 if possible, otherwise calls driving_stop().
    int new_speed = current_speed;
    // Might be better to have constant to store the speed change intervals (e.g. at the
    // moment speed intervals is 10).
    if (current_speed == 0) {
        printf("Error: Motor speed already at zero.\n");
    }
    else if (current_speed <= 10) {
        new_speed = driving_stop();
    }
    else {
        // Decrease driving motor speed value by 5.
        new_speed -= 10;
    }
    return new_speed;
}
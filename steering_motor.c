#include <stdio.h>
#include "pico/stdlib.h"

void steering_motor_setup() {
    // Sets up steering motor.
    printf("Setting up the steering motor...\n");
}

void stop_steering() {
    // Stops steering motor, without shutting it down.
    printf("Stopping steering motor\n");
}

void shutdown_steering_motor() {
    // Shuts down the steering motor.
    stop_steering();
    printf("Shutting down steering motor...\n");
}

void steer_right(int turn_duration) {
    // Steers right.
    printf("Steering right\n");
    sleep_ms(turn_duration);
    stop_steering();
}

void steer_left(int turn_duration) {
    // Steers left.
    printf("Steering left\n");
    sleep_ms(turn_duration);
    stop_steering();
}
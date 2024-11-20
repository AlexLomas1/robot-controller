#include <stdio.h>
#include "pico/stdlib.h"

#define MOTOR_A_PIN_1 3 // IN1 (Forward for Motor A)
#define MOTOR_A_PIN_2 4 // IN2 (Backward for Motor A)

void driving_motor_setup() {
    // Sets up the driving motor.
    printf("Setting up the driving motor.");
    gpio_init(MOTOR_A_PIN_1);
    gpio_set_dir(MOTOR_A_PIN_1, GPIO_OUT);

    gpio_init(MOTOR_A_PIN_2);
    gpio_set_dir(MOTOR_A_PIN_2, GPIO_OUT);
}

int driving_motor_stop() {
    // Stops driving motor.
    gpio_put(MOTOR_A_PIN_1, 0);
    gpio_put(MOTOR_A_PIN_2, 0);

    int new_speed = 0;
    return new_speed;
}

int drive_forwards() {
    // Turns on the driving motor, with the motor speed value (0-255) initialised to 50.
    gpio_put(MOTOR_A_PIN_1, 1);
    gpio_put(MOTOR_A_PIN_2, 0);

    int new_speed = 50; // Placeholder value, set to whatever default speed is.
    return new_speed;
}

int accelerate(int current_speed) {
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
        // Increase motor speed value by 10.
        new_speed += 10;
    }
    return new_speed;
}

int decelerate(int current_speed) {
    // Decreases motor speed value (0-255) by 10 if possible, otherwise calls driving_stop().
    int new_speed = current_speed;
    // Might be better to have constant to store the speed change intervals (e.g. at the
    // moment speed intervals is 10).
    if (current_speed == 0) {
        printf("Error: Motor speed already at zero.\n");
    }
    else if (current_speed <= 10) {
        new_speed = driving_motor_stop();
    }
    else {
        // Decrease driving motor speed value by 10.
        new_speed -= 10;
    }
    return new_speed;
}

int main() {
    // This is just a test sequence. Actual 
    driving_motor_setup();
    while (true) {
        drive_forwards();
        sleep_ms(3000);

        driving_motor_stop();
        sleep_ms(3000);

        drive_forwards();
        sleep_ms(3000);

        driving_motor_stop();
        sleep_ms(2000);
    }
}
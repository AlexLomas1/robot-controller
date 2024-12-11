#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define MOTOR_A_PIN_1 3 // IN1 (Forward for Motor A)
#define MOTOR_A_PIN_2 4 // IN2 (Backward for Motor A)
#define MOTOR_A_PWM_PIN 15 // ENA (PWM Control for Motor A)

void driving_motor_setup() {
    // Sets up the driving motor.
    
    gpio_init(MOTOR_A_PIN_1);
    gpio_set_dir(MOTOR_A_PIN_1, GPIO_OUT);

    gpio_init(MOTOR_A_PIN_2);
    gpio_set_dir(MOTOR_A_PIN_2, GPIO_OUT);

    gpio_set_function(MOTOR_A_PWM_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(MOTOR_A_PWM_PIN);
    pwm_set_wrap(slice_num, 255); // Sets PWM range (0-255) to act as speed control for motor.
    pwm_set_enabled(slice_num, true); // Enable PWM
}

void set_motor_speed(int new_speed) {
    // Changes the speed value (0-255) of the motor.
    // NOTE: testing has shown that current motor doesn't run at a new_speed value of
    // below 80. 
    uint slice_num = pwm_gpio_to_slice_num(MOTOR_A_PWM_PIN);
    pwm_set_gpio_level(MOTOR_A_PWM_PIN, new_speed);
}

int driving_motor_stop() {
    // Stops driving motor.
    gpio_put(MOTOR_A_PIN_1, 0);
    gpio_put(MOTOR_A_PIN_2, 0);
    set_motor_speed(0);

    int new_speed = 0;
    return new_speed;
}

int drive_forwards() {
    // Turns on the driving motor in the forward direction, with the motor speed value 
    // (0-255) initialised to 150.
    gpio_put(MOTOR_A_PIN_1, 1);
    gpio_put(MOTOR_A_PIN_2, 0);
    set_motor_speed(150); // NOTE: testing has shown that current motor doesn't run at a 
    // speed value of below 80.

    int new_speed = 150; // Placeholder value, set to whatever default speed is.
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
        set_motor_speed(255);
    }
    else {
        // Increase motor speed value by 10.
        new_speed += 10;
        set_motor_speed(new_speed);
    }
    return new_speed;
}

int decelerate(int current_speed) {
    // Decreases motor speed value (0-255) by 10 if possible, otherwise stops motor, or an error
    // message will be printed if motor already stopped.
    int new_speed = current_speed;
    // Might be better to have constant to store the speed change intervals (e.g. at the
    // moment speed intervals is 10).
    if (current_speed == 0) {
        printf("Error: Motor speed already at zero.\n");
    }
    else if (current_speed - 10 <= 0) {
        // Stop motor.
        new_speed = driving_motor_stop();
    }
    else {
        // Decrease driving motor speed value by 10.
        new_speed -= 10;
        set_motor_speed(new_speed);
    }
    return new_speed;
}

int main() {
    // This is just a test sequence.
    driving_motor_setup();

    while (true) {
        drive_forwards(); // Gives motor speed of 150
        sleep_ms(1000);

        driving_motor_stop();
        sleep_ms(2000);

        drive_forwards();
        set_motor_speed(255); // Maximum speed
        sleep_ms(1000);

        driving_motor_stop();
        sleep_ms(2000);
    }
}
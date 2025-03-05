#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "../include/driving_motor.h"

#define MOTOR_A_PIN_1 2 // Forwards for Motor A
#define MOTOR_A_PIN_2 3 // Backwards for Motor A
#define MOTOR_A_PWM_PIN 14 // PWM Control for Motor A

#define MOTOR_B_PIN_1 4 // Forwards for Motor B
#define MOTOR_B_PIN_2 5 // Backwards for Motor B
#define MOTOR_B_PWM_PIN 15 // PWM Control for Motor B

void driving_motor_setup() {
    // Sets up the driving motors.
    
    gpio_init(MOTOR_A_PIN_1);
    gpio_set_dir(MOTOR_A_PIN_1, GPIO_OUT);

    gpio_init(MOTOR_A_PIN_2);
    gpio_set_dir(MOTOR_A_PIN_2, GPIO_OUT);

    gpio_init(MOTOR_B_PIN_1);
    gpio_set_dir(MOTOR_B_PIN_1, GPIO_OUT);
    
    gpio_init(MOTOR_B_PIN_2);
    gpio_set_dir(MOTOR_B_PIN_2, GPIO_OUT);

    gpio_set_function(MOTOR_A_PWM_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(MOTOR_A_PWM_PIN);
    pwm_set_wrap(slice_num, 255); // Sets PWM range (0-255) to act as speed control for motor A.
    pwm_set_enabled(slice_num, true); // Enable PWM for motor A.

    gpio_set_function(MOTOR_B_PWM_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(MOTOR_B_PWM_PIN);
    pwm_set_wrap(slice_num, 255); // Sets PWM range (0-255) to act as speed control for motor B.
    pwm_set_enabled(slice_num, true); // Enable PWM for motor B.
}

void set_motor_speed(int new_speed) {
    // Changes the speed value (0-255) of the motors.
    // Note: testing has shown that current motor doesn't run at a new_speed value of
    // below 80. 
    pwm_set_gpio_level(MOTOR_A_PWM_PIN, new_speed);
    pwm_set_gpio_level(MOTOR_B_PWM_PIN, new_speed);
}

void driving_motor_stop() {
    // Stops driving motors.
    gpio_put(MOTOR_A_PIN_1, 0);
    gpio_put(MOTOR_A_PIN_2, 0);
    gpio_put(MOTOR_B_PIN_1, 0);
    gpio_put(MOTOR_B_PIN_2, 0);
    set_motor_speed(0);
}

void drive_forwards() {
    // Turns on the driving motors in the forward direction, with the motor speed value 
    // (0-255) initialised to 150.
    gpio_put(MOTOR_A_PIN_1, 1);
    gpio_put(MOTOR_A_PIN_2, 0);
    gpio_put(MOTOR_B_PIN_1, 1);
    gpio_put(MOTOR_B_PIN_2, 0);
    set_motor_speed(150); 
}

void drive_backwards() {
    // Turn on the driving motors in the backward direction, with the motor speed value 
    // (0-255) initialised to 150.
    gpio_put(MOTOR_A_PIN_1, 0);
    gpio_put(MOTOR_A_PIN_2, 1);
    gpio_put(MOTOR_B_PIN_1, 0);
    gpio_put(MOTOR_B_PIN_2, 1);
    set_motor_speed(150);
}
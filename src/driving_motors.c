#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "../include/driving_motors.h"

#define MOTOR_A_PIN_1 2 // Forwards for Motor A
#define MOTOR_A_PIN_2 3 // Backwards for Motor A
#define MOTOR_A_PWM_PIN 14 // PWM Control for Motor A

#define MOTOR_B_PIN_1 4 // Forwards for Motor B
#define MOTOR_B_PIN_2 5 // Backwards for Motor B
#define MOTOR_B_PWM_PIN 15 // PWM Control for Motor B

#define DEFAULT_SPEED 150

void driving_motors_setup() {
    // Initialises GPIO pins used to control DC motors, and configures PWM for speed control.
    
    gpio_init(MOTOR_A_PIN_1);
    gpio_set_dir(MOTOR_A_PIN_1, GPIO_OUT);

    gpio_init(MOTOR_A_PIN_2);
    gpio_set_dir(MOTOR_A_PIN_2, GPIO_OUT);

    gpio_init(MOTOR_B_PIN_1);
    gpio_set_dir(MOTOR_B_PIN_1, GPIO_OUT);
    
    gpio_init(MOTOR_B_PIN_2);
    gpio_set_dir(MOTOR_B_PIN_2, GPIO_OUT);

    gpio_set_function(MOTOR_A_PWM_PIN, GPIO_FUNC_PWM);
    uint slice_num_a = pwm_gpio_to_slice_num(MOTOR_A_PWM_PIN);
    pwm_set_wrap(slice_num_a, 255); // Sets PWM counter wrap value to 255 for Motor A.
    pwm_set_enabled(slice_num_a, true); // Enable PWM for motor A.

    gpio_set_function(MOTOR_B_PWM_PIN, GPIO_FUNC_PWM);
    uint slice_num_b = pwm_gpio_to_slice_num(MOTOR_B_PWM_PIN);
    pwm_set_wrap(slice_num_b, 255); // Sets PWM counter wrap value to 255 for Motor B.
    pwm_set_enabled(slice_num_b, true); // Enable PWM for motor B.
}

void set_motor_speed(int new_speed) {
    /* Sets the speed value (0-255) of the motors. Note: testing has shown that current motor 
    doesn't run at a new_speed value of below 80. */
    pwm_set_gpio_level(MOTOR_A_PWM_PIN, new_speed);
    pwm_set_gpio_level(MOTOR_B_PWM_PIN, new_speed);
}

void driving_stop() {
    // Stops driving motors by setting all pins to low, with motor speed set to 0 for safety.
    gpio_put(MOTOR_A_PIN_1, 0);
    gpio_put(MOTOR_A_PIN_2, 0);
    gpio_put(MOTOR_B_PIN_1, 0);
    gpio_put(MOTOR_B_PIN_2, 0);
    set_motor_speed(0);
}

void drive_forwards() {
    /* Turns on the driving motors in the forwards direction, with the motor speed value (0-255)
    set to the default speed value. */
    gpio_put(MOTOR_A_PIN_1, 1);
    gpio_put(MOTOR_A_PIN_2, 0);
    gpio_put(MOTOR_B_PIN_1, 1);
    gpio_put(MOTOR_B_PIN_2, 0);
    set_motor_speed(DEFAULT_SPEED); 
}

void drive_backwards() {
    /* Turns on the driving motors in the backwards direction, with the motor speed value (0-255) 
    set to the default speed value. */
    gpio_put(MOTOR_A_PIN_1, 0);
    gpio_put(MOTOR_A_PIN_2, 1);
    gpio_put(MOTOR_B_PIN_1, 0);
    gpio_put(MOTOR_B_PIN_2, 1);
    set_motor_speed(DEFAULT_SPEED);
}
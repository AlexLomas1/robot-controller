#include <stdio.h>
#include "pico/stdlib.h"

#define STEERING_MOTOR_PIN_1 3 // IN1 (Turn right)
#define STEERING_MOTOR_PIN_2 4 // IN2 (Turn left)
#define STEERING_MOTOR_PWM_PIN 15 // ENA (PWM Control for steering motor)
// NOTE: pins used are currently the same as motor A pins in driving_motor. This is just to make it
// easier to test code with just one motor.

void steering_motor_setup() {
    // Sets up steering motor.
    gpio_init(STEERING_MOTOR_PIN_1);
    gpio_set_dir(STEERING_MOTOR_PIN_1, GPIO_OUT);

    gpio_init(STEERING_MOTOR_PIN_2);
    gpio_set_dir(STEERING_MOTOR_PIN_2, GPIO_OUT);

    // PWM setup will go here.
}

void set_steering_speed(int new_speed) {
    // This will use PWM for motor speed control
}

void stop_steering() {
    // Stops steering motor.
    gpio_put(STEERING_MOTOR_PIN_1, 0);
    gpio_put(STEERING_MOTOR_PIN_2, 0);
    set_steering_speed(0);
}

void steer_right(int turn_duration) {
    // Steers right.
    gpio_put(STEERING_MOTOR_PIN_1, 1);
    gpio_put(STEERING_MOTOR_PIN_2, 0);
    set_steer_speed(); // Will set speed to a low (not yet determined) value for more precise turning
    sleep_ms(turn_duration); // Turn duration used to change angle of rotation
    stop_steering();
}

void steer_left(int turn_duration) {
    // Steers left.
    gpio_put(STEERING_MOTOR_PIN_1, 0);
    gpio_put(STEERING_MOTOR_PIN_2, 1);
    set_steer_speed(); // Will set speed to a low (not yet determined) value for more precise turning
    sleep_ms(turn_duration); // Turn duration used to change angle of rotation
    stop_steering();
}
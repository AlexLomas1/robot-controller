#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

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

    gpio_set_function(STEERING_MOTOR_PWM_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(STEERING_MOTOR_PWM_PIN);
    pwm_set_wrap(slice_num, 255); // Sets PWM range (0-255) to act as speed control for motor.
    pwm_set_enabled(slice_num, true); // Enable PWM
}

void set_steering_speed(int new_speed) {
    // Changes the speed value (0-255) of the motor.
    // NOTE: testing has shown that current motor doesn't run at a new_speed value of
    // below 80.
    uint slice_num = pwm_gpio_to_slice_num(STEERING_MOTOR_PWM_PIN);
    pwm_set_gpio_level(STEERING_MOTOR_PWM_PIN, new_speed);
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
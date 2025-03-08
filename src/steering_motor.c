#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "../include/steering_motor.h"

#define STEERING_MOTOR_PIN 10

void steering_motor_setup() {
    // Sets up the servo motor used for steering.
    gpio_set_function(STEERING_MOTOR_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(STEERING_MOTOR_PIN);
    pwm_set_clkdiv(slice_num, 64.0f); // Sets PWM clock divider, 
    pwm_set_wrap(slice_num, 39062); // Sets PWM counter wrap value to 39062.
    // The frequency of the PWM is calculated as (system clock) / (clkdiv * (wrap + 1)), as
    // the PWM counts from 0 to the wrap value, and the clkdiv, as the name implies, divides the system
    // clock. The default system clock for the Pico is 125MHz, so frequency is 125MHz / (64 * 39063),
    // which is approximately 50Hz (or period of 20ms), which is what typical servo motors require.
    pwm_set_enabled(slice_num, true); // Enable PWM for steering motor
}

void set_servo_angle(int pulse_width) {
    // A pulse is sent with a total length of 20ms. The pulse width (time it spends on) is changed
    // between 0.5 and 2.5ms (500 and 2500us). The pulse width determines the angle of the servo motor,
    // with 0.5ms as 90 degrees right, 1.5ms as 0 degrees, and 2.5ms as 90 degrees left.

    uint slice_num = pwm_gpio_to_slice_num(STEERING_MOTOR_PIN);
    // Pulse width (us) is converted to PWM level. As PWM wrap value is 39062, full 20ms period is
    // 39062, so PWM level is calculated as below.
    int level = (pulse_width / 20000) * 39062;
    pwm_set_gpio_level(STEERING_MOTOR_PIN, level);
}

void centre_servo() {
    // Centres the servo motor (0 degrees).
    set_servo_angle(1500);
}

void steer_right(int angle) {
    // Note that angle is in terms of integer multiples of 11.25 degrees (e.g. 0 = 0 degrees, 2 = 22.5 
    // degrees), up to 8 (90 degrees). 
    int pulse_width;

    if (angle >= 0 && angle <= 8) {
        pulse_width = 1500 - (angle * 125);
        set_servo_angle(pulse_width);
    }
}

void steer_left(int angle) {
    // Note that angle is in terms of integer multiples of 11.25 degrees (e.g. 0 = 0 degrees, 2 = 22.5 
    // degrees), up to 8 (90 degrees). 
    int pulse_width;

    if (angle >= 0 && angle <= 8) {
        pulse_width = 1500 + (angle * 125);
        set_servo_angle(pulse_width);
    }
}
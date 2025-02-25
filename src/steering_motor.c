#include <stdio.h>
#include "pico/stdlib.h"
#include "../include/steering_motor.h"

#define STEERING_MOTOR_PIN 10

void steering_motor_setup() {
    // Sets up the servo motor used for steering.
    gpio_init(STEERING_MOTOR_PIN);
    gpio_set_dir(STEERING_MOTOR_PIN, GPIO_OUT);
}

void set_servo_angle(int pulse_width) {
    // A pulse is sent with a total length of 20ms. The pulse width (time it spends on) is changed
    // between 0.5 and 2.5ms (500 and 2500us). The pulse width determines the angle of the servo motor,
    // with 0.5ms as 90 degrees right, 1.5ms as 0 degrees, and 2.5ms as 90 degrees left.

    // Note that while only one pulse needs to be sent, sending multiple seems to make the angle 
    // slightly more consistent.
    int i;

    for (i = 0; i <= 5; i++) {
        gpio_put(STEERING_MOTOR_PIN, 1);
        sleep_us(pulse_width); 
        gpio_put(STEERING_MOTOR_PIN, 0);
        sleep_us(20000 - pulse_width);
    }
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

void test() {
    steering_motor_setup();

    // Test sequence.
    centre_servo();
    sleep_ms(1000);

    int i;
    for (i = 1; i <= 8; i += 1) {
        steer_left(i);
        sleep_ms(250);
    }

    centre_servo();
    sleep_ms(1000);

    for (i = 1; i <= 8; i += 1) {
        steer_right(i);
        sleep_ms(250);
    }
    centre_servo();
}
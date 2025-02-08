#include <stdio.h>
#include "pico/stdlib.h"

#define STEERING_MOTOR_PIN_1 3

void steering_motor_setup() {
    // Sets up the servo motor used for steering.
    gpio_init(STEERING_MOTOR_PIN_1);
    gpio_set_dir(STEERING_MOTOR_PIN_1, GPIO_OUT);
}

void set_servo_angle(int pulse_width) {
    // A pulse is sent with a total length of 20ms. The pulse width (time it spends on) is changed
    // between 0.5 and 2.5ms (500 and 2500us). The pulse width determines the angle of the servo motor,
    // with 0.5ms as 0 degrees, 1.5ms as 90 degrees (neutral), and 2.5ms as 180 degrees.
    gpio_put(STEERING_MOTOR_PIN_1, 1);
    sleep_us(pulse_width); // us used instead of ms as sleep functions only take integer paramters, so 
    // for example 0.5ms can't be done with sleep_ms
    gpio_put(STEERING_MOTOR_PIN_1, 0);
    sleep_us(20000 - pulse_width);
}

void main() {
    steering_motor_setup();

    // Test sequence. Each 250us change in pulse width is about 22.5 degrees of rotation
    int pulse_width;
    for (pulse_width = 500; pulse_width <= 2500; pulse_width += 250) {
        set_servo_angle(pulse_width);
        sleep_ms(250);
    }
    for (pulse_width = 2250; pulse_width >= 500; pulse_width -= 250) {
        set_servo_angle(pulse_width);
        sleep_ms(250);
    }
}
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

void driving_motor_stop() {
    // Stops driving motor.
    set_motor_speed(0);
    gpio_put(MOTOR_A_PIN_1, 0);
    gpio_put(MOTOR_A_PIN_2, 0);
}

void drive_forwards() {
    // Turns on the driving motor in the forward direction, with the motor speed value 
    // (0-255) initialised to 150.
    gpio_put(MOTOR_A_PIN_1, 1);
    gpio_put(MOTOR_A_PIN_2, 0);
    set_motor_speed(150); // Placeholder value.
}

void drive_backwards() {
    // Turn on the driving motor in the backward direction, with the motor speed value 
    // (0-255) initialised to 150.
    gpio_put(MOTOR_A_PIN_1, 0);
    gpio_put(MOTOR_A_PIN_2, 1);
    set_motor_speed(150); // Placeholder value.
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
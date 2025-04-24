#include "pico/stdlib.h"
#include "../include/driving_motors.h" // Allows functions from driving_motor.c to be called here
#include "../include/steering_motor.h" // Allows functions from steering_motor.c to be called here

#define TX_PIN 0
#define RX_PIN 1

void uart_setup() {
    // Sets up the UART instance.
    // Initialises the UART to a baud rate of 115200.
    uart_init(uart0, 115200);
    /* Note that some GPIO pins that support UART TX/RX use uart1 instead. You can see which at pages
    145-150 of https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf */

    // Initialises GPIO pins used for UART communication.
    gpio_init(TX_PIN);
    gpio_set_function(0, GPIO_FUNC_UART);

    gpio_init(RX_PIN); 
    gpio_set_function(1, GPIO_FUNC_UART);
}

void master_setup() {
    /* Initialises the main subsystems of the robot, including the driving motors, the steering motor,
    and the UART instance. */
    driving_motors_setup();
    steering_motor_setup();
    uart_setup();
    uart_puts(uart0, "hello, world\n");
}

int main() {
    master_setup();
    int received_value, user_input_num;
    char user_input_char;

    while (true) {
        if (uart_is_readable(uart0)) {
            // Reads input from UART.
            received_value = uart_getc(uart0); // Gets the ASCII value of entered character.
            user_input_char = received_value; // Converts ASCII value back to character.

            switch (user_input_char) {
                case 'f': // Drive forwards
                    uart_puts(uart0, "Driving forwards\n");
                    drive_forwards();
                    break;
                
                case 'b': // Drive backwards
                    uart_puts(uart0, "Driving backwards\n");
                    drive_backwards();
                    break;

                case 'c': // Change driving motors' speed
                    received_value = uart_getc(uart0);
                    user_input_num = received_value - 48; // Converts ASCII '0'-'9' to integer 0-9.
                    if (user_input_num >= 0 && user_input_num <= 9) { // Input validation
                        /* Maps input value (0-9) to a motor speed (80-251). This covers most of the 
                        effective motor speed range (0-255), as testing has shown that motor doesn't
                        run at speeds of below 80. */
                        int new_speed = (user_input_num * 19) + 80;
                        uart_puts(uart0, "Changing speed \n");
                        set_motor_speed(new_speed);
                    }
                    else {
                        uart_puts(uart0, "Invalid speed value\n");
                    } 
                    break;
                
                case 's': // Stop driving motors
                    uart_puts(uart0, "Stopping driving motors\n");
                    driving_stop();
                    break;

                case 'r': // Turn right
                    received_value = uart_getc(uart0);
                    user_input_num = received_value - 48; // Converts ASCII '0'-'9' to integer 0-9.
                    if (user_input_num == 0) {
                        uart_puts(uart0, "Returning to neutral steering\n");
                        centre_servo();
                    }
                    else if (user_input_num >= 1 && user_input_num <= 9) { // Input validation
                        uart_puts(uart0, "Turning right\n");
                        // Steers to the right by the given number of 10° steps.
                        steer_right(user_input_num); 
                    }
                    else {
                        uart_puts(uart0, "Invalid steering magnitude\n");
                    }
                    break;
                    
                case 'l': // Turn left
                    received_value = uart_getc(uart0);
                    user_input_num = received_value - 48; // Converts ASCII '0'-'9' to integer 0-9.
                    if (user_input_num == 0) {
                        uart_puts(uart0, "Returning to neutral steering\n");
                        centre_servo();
                    }
                    else if (user_input_num >= 1 && user_input_num <= 9) { // Input validation
                        uart_puts(uart0, "Turning left\n");
                        // Steers to the left by the given number of 10° steps.
                        steer_left(user_input_num);
                    }
                    else {
                        uart_puts(uart0, "Invalid steering magnitude\n");
                    }
                    break;

                case 'm': // Centre servo
                    uart_puts(uart0, "Returning to neutral steering\n");
                    centre_servo();
                    break;
                    
                default: // In case of an invalid command.
                    uart_puts(uart0, "Unknown input\n");
            }
            sleep_ms(250); // Delay to prevent multiple actions being attempted at once.
        }
    }
}
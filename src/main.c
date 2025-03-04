#include <stdio.h>
#include "pico/stdlib.h"
#include "../include/driving_motor.h" // Allows functions from driving_motor.c to be called here
#include "../include/steering_motor.h" // Allows functions from steering_motor.c to be called here

void uart_setup() {
    // Sets up the UART instance.
    // Initialise the UART to a baud rate of 115200.
    uart_init(uart0, 115200);

    // Initialise pins used for UART communication.
    gpio_init(0); // TX Pin
    gpio_set_function(0, GPIO_FUNC_UART);

    gpio_init(1); // RX Pin
    gpio_set_function(1, GPIO_FUNC_UART);
}

int main() {
    // To do: could potentially call all the initialising functions from a master_setup() function.
    // Also: could change function names to use init instead of setup (e.g. driving_motor_init), as this
    // seems to be the standard (such as with stdio_init_all, gpio_init) - only problem is that the name
    // uart_init is already in use.
    stdio_init_all();
    driving_motor_setup();
    steering_motor_setup();
    uart_setup();
    uart_puts(uart0, "hello, world\n");
    int user_input, received_num, i;

    while (true) {
        if (uart_is_readable(uart0)) {
            // Reads input from UART
            user_input = uart_getc(uart0); // Gets the ASCII value of entered character.

            switch (user_input) {
                case 102: // ASCII value of f - Drive forwards
                    uart_puts(uart0, "Driving forwards\n");
                    drive_forwards();
                    break;
                
                case 98: // ASCII value of b - Drive backwards
                    uart_puts(uart0, "Driving backwards\n");
                    drive_backwards();
                    break;

                case 99: // ASCII value of c - Change speed
                    user_input = uart_getc(uart0);
                    received_num = user_input - 48; // Recieves a number 0 to 9 based on its ASCII value
                    if (received_num >= 0 && received_num <= 9) {
                        // Converts received num to a value 80-251, to cover most of the speed values (0-255,
                        // but testing has shown that motor doesn't run at a speed of below 80).
                        int new_speed = (received_num * 19) + 80;
                        uart_puts(uart0, "Changing speed \n");
                        set_motor_speed(new_speed);
                    }
                    else {
                        uart_puts(uart0, "Invalid speed value\n");
                    } 
                    break;
                
                case 115: // ASCII value of s - Stop driving
                    uart_puts(uart0, "Stopping driving motor\n");
                    driving_motor_stop();
                    break;

                case 114: // ASCII value of r - Turn right
                    user_input = uart_getc(uart0);
                    received_num = user_input - 48; // Recieves a number 0 to 8 based on its ASCII value
                    if (received_num >= 0 && received_num <= 8) {
                        uart_puts(uart0, "Turning right\n");
                        steer_right(received_num);
                    }
                    else {
                        uart_puts(uart0, "Invalid steering magnitude\n");
                    }
                    break;
                    
                case 108: // ASCII value of l - Turn left
                    user_input = uart_getc(uart0);
                    received_num = user_input - 48; // Recieves a number 0 to 8 based on its ASCII value
                    if (received_num >= 0 && received_num <= 8) {
                        uart_puts(uart0, "Turning left\n");
                        steer_left(received_num);
                    }
                    else {
                        uart_puts(uart0, "Invalid steering magnitude\n");
                    }
                    break;

                case 109: // ASCII value of m - Centres servo
                    uart_puts(uart0, "Returning to neutral steering\n");
                    centre_servo();
                    break;
                    
                default:
                    uart_puts(uart0, "Unknown input\n");
            }
            sleep_ms(250); // Delay to prevent multiple actions being attempted at once.
        }
    }
}          
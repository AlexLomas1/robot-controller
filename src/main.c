#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
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

    int i;
    while (true) {
        if (uart_is_readable(uart0)) {
            // Reads input from UART
            int user_input = uart_getc(uart0); // Gets the ASCII value of entered character.

            if (user_input == 102) { // ASCII value of f for forwards
                uart_puts(uart0, "Driving forwards\n");
                drive_forwards();
            }

            else if (user_input == 98) { // ASCII value of b for backwards
                uart_puts(uart0, "Driving backwards\n");
                drive_backwards();
            }

            else if (user_input == 115) { // ASCII value of s for stop
                uart_puts(uart0, "Stopping driving motor\n");
                driving_motor_stop();
            }

            else if (user_input == 114) { // ASCII value of r for right
                uart_puts(uart0, "Turning right\n");
                for (i = 1; i <= 8; i += 1) {
                    steer_right(i);
                    sleep_ms(100);
                }
            }

            else if (user_input == 108) { // ASCII value of l for left
                uart_puts(uart0, "Turning left\n");
                for (i = 1; i <= 8; i += 1) {
                    steer_left(i);
                    sleep_ms(100);
                }
            }

            else if (user_input == 109) { // ASCII value of m for middle
                uart_puts(uart0, "Returning to neutral steering\n");
                steer_left(0);
            }

            else {
                uart_puts(uart0, "Unknown input\n");
            }
        }
        sleep_ms(250); // Delay to prevent multiple actions being attempted at once.
    }           
}
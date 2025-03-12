#include "pico/stdlib.h"
#include "../include/driving_motors.h" // Allows functions from driving_motor.c to be called here
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

void master_setup() {
    // Calls all relevent setup/initialisation functions
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

                case 'c': // Change speed
                    received_value = uart_getc(uart0);
                    user_input_num = received_value - 48; // Recieves a number 0 to 9 based on its ASCII value
                    if (user_input_num >= 0 && user_input_num <= 9) {
                        // Converts received num to a value 80-251, to cover most of the speed values (0-255,
                        // but testing has shown that motor doesn't run at a speed of below 80).
                        int new_speed = (user_input_num * 19) + 80;
                        uart_puts(uart0, "Changing speed \n");
                        set_motor_speed(new_speed);
                    }
                    else {
                        uart_puts(uart0, "Invalid speed value\n");
                    } 
                    break;
                
                case 's': // Stop driving
                    uart_puts(uart0, "Stopping driving motors\n");
                    driving_stop();
                    break;

                case 'r': // Turn right
                    received_value = uart_getc(uart0);
                    user_input_num = received_value - 48; // Recieves a number 0 to 8 based on its ASCII value
                    if (user_input_num >= 0 && user_input_num <= 8) {
                        uart_puts(uart0, "Turning right\n");
                        steer_right(user_input_num);
                    }
                    else {
                        uart_puts(uart0, "Invalid steering magnitude\n");
                    }
                    break;
                    
                case 'l': // Turn left
                    received_value = uart_getc(uart0);
                    user_input_num = received_value - 48; // Recieves a number 0 to 8 based on its ASCII value
                    if (user_input_num >= 0 && user_input_num <= 8) {
                        uart_puts(uart0, "Turning left\n");
                        steer_left(user_input_num);
                    }
                    else {
                        uart_puts(uart0, "Invalid steering magnitude\n");
                    }
                    break;

                case 'm': // Centres servo
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
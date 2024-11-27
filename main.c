#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

void uart_setup() {
    // Sets up the UART.
    // Initialise the UART to a baud rate of 115200.
    uart_init(uart0, 115200);

    gpio_init(0); // TX Pin
    gpio_init(1); // RX Pin

    gpio_set_function(0, GPIO_FUNC_UART); 
    gpio_set_function(1, GPIO_FUNC_UART);
}

int main() {
    stdio_init_all();
    uart_setup();
    while (true) {
        if (uart_is_readable(uart0)) {
            // Reads input from UART
            int user_input = uart_getc(uart0); // Gets the ASCII value of entered character.
            if (user_input == 102) { // ASCII value of f
                uart_puts(uart0, "Forward\n");
            }
            else if (user_input == 98) { // ASCII value of b
                uart_puts(uart0, "Backward\n");
            }
            else {
                uart_puts(uart0, "Unknown input\n");
            }
        }
        sleep_ms(500); // Delay to prevent multiple actions being attempted at once.
    }           
}
// Initialises GPIO pins used to control DC motors, and configures PWM for speed control.
void driving_motors_setup();

// Sets the motor speed (0-255). Note: speed values of below 80 may not produce movement.
void set_motor_speed(int new_speed);

// Stops driving motors by setting all pins to low, with motor speed set to 0 for safety.
void driving_stop();

// Turns on the driving motors in the forward direction at the default speed.
void drive_forwards(); 

// Turns on the driving motors in the backwards direction at the default speed.
void drive_backwards(); 
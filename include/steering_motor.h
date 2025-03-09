// Initialises the GPIO pin for the servo motor used in steering.
void steering_motor_setup(); 

/* Sets the angle of the servo motor with PWM control. Pulse width should be between 500us (90°
right) and 2500us (90° left) */
void set_servo_angle(int pulse_width); 

// Centres the servo motor (0°).
void centre_servo();

// Steers to the right by a given number (0-8) of 11.25° steps (0-90°).
void steer_right(int angle);

// Steers to the left by a given number (0-8) of 11.25° steps (0-90°).
void steer_left(int angle);
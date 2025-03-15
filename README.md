## About

This software is designed to control a Raspberry Pi Pico-based robot using user inputs. It provides basic functionality for propulsion, speed control, and steering. 

## Features

* Propulsion via DC motors.
* Speed control through use of Pulse-Width Modulation (PWM) signals.
* Steering with a servo motor controlled by PWM signals.
* User control via UART using text inputs.

## Input Commands

The robot is controlled using simple text commands sent using UART. All valid commands are shown below.

| Command | Description                                         |
|:-------:|-----------------------------------------------------|
|    f    | Turn on the driving motors to drive forwards        |
|    b    | Turn on the driving motors to drive backwards       |
|  c[v]  | Sets the driving motor speed to v (0 ≤ v ≤ 9)      |
|    s    | Stop the driving motors                             |
|  r[θ]  | Sets the servo angle to θ (0 ≤ θ ≤ 8) to the right |
|  l[θ]  | Sets the servo angle to θ (0 ≤ θ ≤ 8) to the left  |
|    m    | Centres the servo motor                             |

Note: the commands should be written without the square brackets - e.g. c2,  not c[2].

### Motor speed calculation

The actual motor speed (0-255) is calculated by (v * 19) + 80. This gives a value between 80 and 251, as testing has shown that the DC motors don't operate at a speed of below 80.

### Servo angle calculation

The angle θ corresponds to (θ * 11.25)°, so the servo can move from 90° left to 90° right in 11.25° increments. Given that most servo motors are not that precise, the actual angle may vary.

## Installation and Usage

### Prerequisites
Before installing, ensure you have:
* The [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) installed and set up. 
* CMake, which can be downloaded from [cmake.org](https://cmake.org/).

### Clone the repository
```
git clone https://github.com/AlexLomas1/robot-controller
```

### Build the project
```
cd robot-controller
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Load the compiled project into the Pico
After running `cmake --build . --config Release`, a .uf2 file will be generated within the build folder of the project.
1. Connect the Pico to your device while holding down the BOOTSEL button.
2. Copy the generated .uf2 file into the new USB device that appears.

## Dependencies

All of the libraries used within this software are included in version 2.0.0 of the [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk).

The following libraries from the SDK are used in this project:
* pico_stdio
* hardware_gpio
* hardware_pwm
* hardware_uart

Note: Instead of directly referencing the pico_stdio, hardware_gpio, and hardware_uart libraries, this project includes pico_stdlib, which aggregates these libraries along with others.
# About

This software is designed for a user-controlled Raspberry Pi Pico-based robot. It provides basic propulsion, speed control, and steering functionality, and features UART-based communication for real-time user control.

## Table of Contents
- [Features](#features)
- [Input Commands](#input-commands)
- [Installation and Usage](#installation-and-usage)
    - [Software](#software)
    - [Hardware Implementation](#hardware-implementation)
- [Dependencies](#dependencies)

## Features

* Propulsion via DC motors.
* Speed control through use of Pulse-Width Modulation (PWM) signals.
* Steering with a servo motor controlled by PWM signals.
* User control via UART using text inputs.

## Input Commands

The robot is controlled using simple text commands sent using UART. All valid commands are shown below.

| Command | Description                                                       |
|:-------:|-------------------------------------------------------------------|
|    f    | Turns on the driving motors to drive forwards                     |
|    b    | Turns on the driving motors to drive backwards                    |
|   c[v]  | Sets the driving motor speed to v (0 ≤ v ≤ 9)                     |
|    s    | Stops the driving motors                                          |
|   r[θ]  | Sets the servo angle to θ $$\times$$ 10° (0 ≤ θ ≤ 9) to the right |
|   l[θ]  | Sets the servo angle to θ $$\times$$ 10° (0 ≤ θ ≤ 9) to the left  |
|    m    | Centres the servo motor                                           |

Note: the commands should be written without the square brackets - e.g. c2,  not c[2].

### Motor speed calculation

The actual motor speed is given by a value from 0-255, as this is the PWM wrap value used for the motor speed control. For $$v=0$$, the motor is just stopped. For non-zero values of $$v$$, the speed value is calculated by:

$$(v \times 21) + 60$$ 

This gives a value between 81 and 249, which covers most of the motor's effective range as testing has shown that my DC motors don't operate at a speed value of below 80.

## Installation and Usage

### Software
#### Prerequisites
Before installing, ensure you have:
* The [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) installed and set up. 
* CMake, which can be downloaded from [cmake.org](https://cmake.org/).

#### Clone the repository
```
git clone https://github.com/AlexLomas1/robot-controller
```

#### Build the project
```
cd robot-controller
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

#### Load the compiled project into the Pico
After running `cmake --build . --config Release`, a .uf2 file will be generated within the build folder of the project.
1. Connect the Pico to your device while holding down the BOOTSEL button.
2. Copy the generated .uf2 file into the new USB device that appears.

### Hardware Implementation
#### Components
This project makes use of the following electronic components:
* Raspberry Pi Pico microcontroller
* 2 DC motors - SPG10 gearmotors
* Motor driver - L298N
* Servo motor - MG90S micro servo
* USB-to-serial cable - CH340 USB-to-TTL serial cable
* Jumper wires
* Power source - 9V battery

#### Wiring
Note that the following uses the example components listed above, as such the wiring may differ slightly if using different components.

|      Component      | Raspberry Pi Pico Pin |       Other      |
|:-------------------:|:---------------------:|:----------------:|
|   Motor Driver IN1  |          GP2          |        ---       |
|   Motor Driver IN2  |          GP3          |        ---       |
|   Motor Driver IN3  |          GP4          |        ---       |
|   Motor Driver IN4  |          GP5          |        ---       |
|   Motor Driver ENA  |          GP14         |        ---       |
|   Motor Driver ENB  |          GP15         |        ---       |
|  Motor Driver +12V  |          None         | Battery Positive |
|   Motor Driver GND  |      Any GND Pin      | Battery Negative |
|  Servo Motor Power  |          VBUS         |        ---       |
|  Servo Motor Signal |          GP10         |        ---       |
|   Servo Motor GND   |      Any GND Pin      |        ---       |
|  USB to Serial RXI  |          GP0          |        ---       |
|  USB to Serial TXO  |          GP1          |        ---       |
| USB to Serial Power |          None         |        ---       |
|  USB to Serial GND  |      Any GND Pin      |        ---       |

#### Power
* In the above example, the Raspberry Pi Pico is powered via USB. However, you could opt to power it using an external source instead.
* The motor driver should be powered using a separate battery pack.
* Ensure that there is a common ground between the Pico, motor driver, servo motor, and the USB-to-serial cable.

## Dependencies

All of the libraries used within this software are included in version 2.0.0 of the [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk).

The following libraries from the SDK are used in this project:
* pico_stdio
* hardware_gpio
* hardware_pwm
* hardware_uart

Note: Instead of directly referencing the pico_stdio, hardware_gpio, and hardware_uart libraries, this project includes pico_stdlib, which aggregates these libraries along with others.

# ATmega328P-SDK

Collection of drivers written in C language to use the ATmega328P peripherals.

## Project structure

| Directory | Description |
| --------- | ----------- |
| `src`     | Contains the source code |
| `include` | Contains the header files |
| `tools/cmake` | Contains cmake scripts to use the AVR toolchain |

## Features

Implemented drivers:

- [x] I/O ports
- [ ] Timers
- [ ] ADC
- [X] USART
- [ ] SPI
- [X] 2-Wire interface (I2C)
- [ ] Watchdog timer
- [ ] Analog comparator
- [ ] Interrupts

## Dependencies

This project uses the `GNU AVR toolchain`

- `avr-gcc`
- `avr-g++`
- `avr-binutils`
- `avr-libc`

## Usage

Export the sdk path to an environment variable

```shell
export MEGA328P_SDK_PATH=<sdk path>
```

Add the sdk directory to the main CMake file of your project

```cmake
cmake_minimum_required(VERSION 3.30)
project(<project_name> C)

# Include SDK path
add_subdirectory($ENV{MEGA328P_SDK_PATH} sdk)

# Project content
```

### Building the project

Create a directory named `build` and navigate to it

```shell
mkdir build
cd build
```

Execute `cmake` specifying the cmake toolchain file

```shell
cmake -S .. -B . -DCMAKE_TOOLCHAIN_FILE=$MEGA328P_SDK_PATH/tools/cmake/avr-toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```

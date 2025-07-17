# ATmega328P-SDK

This repository contains a set of drivers written in C language to use the different ATmega328P-SDK
peripherals.

## Project structure

| Directory | Description |
| --------- | ----------- |
| `src`     | Contains the source code |
| `test`    | Contains programs to test the different features |
| `tools/cmake` | Contains cmake scripts to use the AVR toolchain |

## Features

Implemented drivers:

- [x] I/O ports (`io_pin.h`)
- [x] Timers
- [x] ADC
- [x] USART
- [ ] SPI
- [x] 2-Wire interface (I2C)
- [ ] Watchdog timer
- [ ] Analog comparator
- [ ] Interrupts

## Dependencies

This project uses the `GNU AVR toolchain`

- `avr-gcc`
- `avr-g++`
- `avr-binutils`
- `avr-libc`

## Building the project

Create a directory named `build` and navigate to it

```shell
mkdir build
cd build
```

Execute `cmake` specifying the cmake toolchain file

```shell
cmake -S .. -B . -DCMAKE_TOOLCHAIN_FILE=../tools/cmake/avr-toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```


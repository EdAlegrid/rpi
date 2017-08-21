# rpi
A lightweight Peripherals Register Control C library for Raspberry Pi

#### Supports the following ARM peripherals

* GPIO 
* PWM  
* I2C (master)  
* SPI

## Compatibility

* Raspberry Pi Models: B+, 2, 3, Zero & Zero W.

## Quick Start

In your Raspberry Pi desktop, clone the rpi repository.
```console
$ git clone https://github.com/EdAlegrid/rpi
$ cd rpi
$ gcc -Wall -pedantic -c rpi.c -o rpi.o -std=c11
```

To compile the sample applications in the same folder.
```console
$ gcc -Wall -pedantic event.c rpi.o -o event -std=c11
```

To run the application.
```console
$ sudo ./event
```

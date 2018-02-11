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

In your Raspberry Pi, clone the rpi repository.
```console
$ git clone https://github.com/EdAlegrid/rpi
```

Compile the library locally within the rpi folder.
```console
$ cd rpi
$ gcc -Wall -pedantic -c rpi.c -o rpi.o -std=c11
```

Compile the sample applications (event.c, pwm.c, i2c.c and spi.c) in the same folder.
```console
$ gcc -Wall -pedantic event.c rpi.o -o event -std=c11
```

Run the application.
```console
$ sudo ./event
```

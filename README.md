# rpi

This is a lightweight direct register control C library for Raspberry Pi devices

#### Supports the following ARM peripherals

* GPIO 
* PWM  
* I2C (master)  
* SPI

## Compatibility

This library will generally work for all Raspberry Pi 40-pin models.

* Raspberry Pi Models: B+, 2, 3, 4, Zero & Zero W.

## Setup Guide

In your Raspberry Pi, clone the rpi repository.
```console
$ git clone https://github.com/EdAlegrid/rpi
```
Compile the rpi source code and create an object file within the obj folder. 
```console
$ cd rpi
$ gcc -Wall -pedantic -c src/rpi.c -o obj/rpi.o -std=c11
```
Compile the sample applications (event.c, pwm.c, i2c.c and spi.c). This process will link the source applications with the rpi object code to create a binary executable file.   
```console
$ gcc -Wall -pedantic event.c obj/rpi.o -o event -std=c11
```

Run the application.
```console
$ sudo ./event
```

## License

GNU General Public License v3.0

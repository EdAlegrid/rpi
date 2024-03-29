# rpi

Rpi is a lightweight and simple C library for Raspberry Pi using direct register control.

It maps the peripheral registers in memory using */dev/mem* for PWM, I2C, SPI and */dev/gpiomem* for GPIO control.

It is mainly used for **iiot** and **m2m** applications. 

### Supports the following ARM peripherals

* GPIO 
* PWM  
* I2C (master)  
* SPI

# Supported Raspberry Pi Devices
* Model: Pi Zero & Zero W, Pi Zero 2 W, Pi 3 Model B+, Pi 4 Model B, Compute Module 3 & 4 (Generally most of the 40-pin models)

# Supported OS
Tried and tested on the following OS
- Raspbian
- Raspberry Pi OS (32 and 64-bit)
- 64-bit Ubuntu 20+ (Only GPIO peripheral is supported)


# Setup Guide
### Download the repo
In your Raspberry Pi, clone the rpi repository.
```console
$ git clone https://github.com/EdAlegrid/rpi
```

Go inside the directory to compile the library and the sample applications.
```console
$ cd rpi
```
### Compile the library
Compile the rpi source code and create an object file within the obj folder. 
```console
$ gcc -Wall -pedantic -c src/rpi.c -o obj/rpi.o
```

### Compile your application
Compile the sample applications (gpio.c, pwm.c, i2c.c and others).

**e.g.** compiling the pwm.c ...
```console
$ gcc -Wall -pedantic pwm.c obj/rpi.o -o pwm
```

Run the application.
```console
$ sudo ./pwm
```

# License

GNU General Public License v3.0

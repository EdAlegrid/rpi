/*
 * This is a low-level Peripherals Control Library for ARM-based SBC's such as Raspberry Pi 1 Model B+, 2, 3 and Pi Zero W.
 *
 * Copyright (c) 2017 Ed Alegrid <ealegrid@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/* Defines for RPI */
#ifndef RPI_H
#define RPI_H

#include <stdint.h>

#define RPI_VERSION 100 /* Version 1.00 */

#ifdef __cplusplus
extern "C" {
#endif


/****************************
   Initialize RPI library 
*****************************/
extern void rpi_init(); 

/***********************
   Close RPI library 
************************/
extern uint8_t rpi_close();

/*********************
     Time Delays
**********************/
extern void nswait(uint64_t ns);  //nanosecond time delay

extern void uswait(uint32_t us);  //microsecond time delay

extern void mswait(uint32_t ms);  //millisecond time delay

/*********************
	GPIO
**********************/
extern void gpio_config(uint8_t pin, uint8_t mode);

extern void gpio_input(uint8_t pin);

extern void gpio_output(uint8_t pin);

extern uint8_t gpio_write(uint8_t pin, uint8_t bit);

extern uint8_t gpio_read(uint8_t pin);

extern void gpio_reset_all_events(uint8_t pin);

extern void gpio_enable_high_event(uint8_t pin, uint8_t bit);

extern void gpio_enable_low_event(uint8_t pin, uint8_t bit);

extern void gpio_enable_rising_event(uint8_t pin, uint8_t bit);

extern void gpio_enable_falling_event(uint8_t pin, uint8_t bit);

extern void gpio_enable_async_rising_event(uint8_t pin, uint8_t bit);

extern void gpio_enable_async_falling_event(uint8_t pin, uint8_t bit);

extern uint8_t gpio_detect_input_event(uint8_t pin);

extern void gpio_reset_event(uint8_t pin);

extern void gpio_enable_pud(uint8_t pin, uint8_t value);

/********************
	PWM
********************/
extern void pwm_set_pin(uint8_t pin);

extern void pwm_reset_pin(uint8_t pin);

extern void pwm_reset_all_pins();

extern uint8_t pwm_set_clock_freq(uint32_t divider);

extern uint8_t pwm_clk_status();

extern void pwm_enable(uint8_t pin, uint8_t n);

extern void pwm_set_mode(uint8_t pin, uint8_t n);

extern void pwm_set_pola(uint8_t pin, uint8_t n);

extern void pwm_set_data(uint8_t pin, uint32_t data);

extern void pwm_set_range(uint8_t pin, uint32_t range);

/*********************
 	I2C
**********************/
extern int i2c_start();

extern void i2c_stop();

extern void i2c_select_slave(uint8_t addr);

extern void i2c_set_clock_freq(uint16_t divider);

extern void i2c_data_transfer_speed(uint32_t baud);

extern uint8_t i2c_write(const char * wbuf, uint8_t len);

extern uint8_t i2c_read(char * rbuf, uint8_t len);

extern uint8_t i2c_byte_read(void);

/********************
	SPI
*********************/
extern int spi_start();

extern void spi_stop();

extern void spi_set_clock_freq(uint16_t divider);

extern void spi_set_data_mode(uint8_t mode);

extern void spi_set_chip_select_polarity(uint8_t cs, uint8_t active);

extern void spi_chip_select(uint8_t cs);

extern void spi_data_transfer(char* wbuf, char* rbuf, uint8_t len);

extern void spi_write(char* wbuf, uint8_t len);

extern void spi_read(char* rbuf, uint8_t len);



#ifdef __cplusplus
}
#endif

#endif /* RPI_H */


















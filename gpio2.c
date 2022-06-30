/****************************************************

   GPIO Input/Output Example
    
   Input event detection using async_rising edge

   Author: Ed Alegrid

*****************************************************/

/* 
 * You may need to modify your RPI config file /boot/config.txt and add the following:
 *
 * dtoverlay=gpio-no-irq
 *
 *
 * Reboot your system.
 *
 * This will disable GPIO interrupts and avoids crashes with newer kernels when using edge interrupts.
 * 
 */



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>

//#include "rpi.h"
#include "./src/rpi.h" // event2.c in root folder
//#include "../src/rpi.h"  // event2.c in /app folder

/**
 GPIO Pin to PHY Pin (board header pin number)
 GPIO 17 / PHY 11
 GPIO 27 / PHY 13
 GPIO 13 / PHY 33 
 GPIO 20 / PHY 38 
*/

/**
 * Circuit Setup
 *
 * Connect momentary switch buttons to inputPin (pin 11) and inputPin2 (pin 13).
 * Connect LED's to outputPin (pin 33) and statusPin (pin 38).
 */

/* input pins */
uint8_t inputPin = 17;  //switch to turn ON  LED output
uint8_t inputPin2 = 27; //switch to turn OFF LED output

/* output pins */
uint8_t outputPin = 13; //LED output
uint8_t statusPin = 20; //LED status indicator

/* Ctrl-C handler */
void sighandler(int signum)
{
   	printf("\nsighandler invoked %d, exiting ...\n", signum);
		gpio_reset_all_events(inputPin);
    gpio_reset_all_events(inputPin2);

    gpio_write(statusPin, 0);  //turn OFF
    gpio_config(statusPin, 0); //set to GPIO input
		gpio_write(outputPin, 0);  //turn OFF
    gpio_config(outputPin, 0); //set to GPIO input

    puts("closing rpi ...");
   	rpi_close();
   	exit(1);
}

/************
    main
*************/
int main(void){

		signal(SIGINT, sighandler);

  	puts("starting rpi ...");
		rpi_init(0);
    /* set statusPin to GPIO output */
  	gpio_config(statusPin, 1);

  	/* set outputPin to GPIO output */
  	gpio_config(outputPin, 1);
  	/* set outputPin initial state to OFF */
  	gpio_write(outputPin, 0);

    /* set inputPin and inputPin2 to GPIO inputs */
		gpio_config(inputPin, 0);
    gpio_config(inputPin2, 0);

  	/* reset any previous input events setup */
  	gpio_reset_all_events(inputPin);
  	gpio_reset_all_events(inputPin2);

  	/* enable async_rising edge detection event */
  	gpio_enable_async_rising_event(inputPin, 1);
  	gpio_enable_async_rising_event(inputPin2, 1);

  	puts("starting GPIO Input Pin Event Detection loop");
  	while(1) {
    		gpio_write(statusPin, 1);
        /* press inputPin switch to turn ON LED output */
    		if(gpio_detect_input_event(inputPin)){
				puts("turning ON  outputPin ...");
      			gpio_write(outputPin, 1);
				gpio_reset_event(inputPin);
    		}

				/* press inputPin2 switch to turn OFF LED output */
    		if(gpio_detect_input_event(inputPin2)){
 				puts("turning OFF outputPin ...");
      			gpio_write(outputPin, 0);
				gpio_reset_event(inputPin2);
    		}

        /* status LED will blink, indicates loop is running */
    		mswait(300);
    		gpio_write(statusPin, 0);
    		mswait(200);
 	}
}

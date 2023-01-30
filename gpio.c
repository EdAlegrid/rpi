/************************

   GPIO Input/Output Example

   Author: Ed Alegrid

************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>

#include "./src/rpi.h"

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
 * Connect momentary switch buttons to GPIO 17 (pin 11) and GPIO 27 (pin 13).
 * Connect LED's to GPIO 13 (pin 33) and GPIO 20 (pin 38).
 */

/* input pins */
uint8_t inputPin1 = 17;		// switch to turn ON  LED output
uint8_t inputPin2 = 27;		// switch to turn OFF LED output

/* output pins */
uint8_t outputPin = 13;		// LED output
uint8_t statusPin = 20;		// LED status indicator

/* Ctrl-C handler */
void sighandler(int signum)
{
   	printf("\nsighandler invoked %d, exiting ...\n", signum);
	gpio_reset_all_events(inputPin1);
        gpio_reset_all_events(inputPin2);

        gpio_write(statusPin, 0);  // turn OFF statusPin
        gpio_config(statusPin, 0); // set to GPIO input
	gpio_write(outputPin, 0);  // turn OFF outputPin
        gpio_config(outputPin, 0); // set to GPIO input
        
        puts("closing rpi ...");
   	rpi_close();
   	exit(1);
}

/************

    main

*************/
int main(void){
 
	signal(SIGINT, sighandler);
  
  	puts("Initializing rpi ...");
  	rpi_init(0);
  
        /* set statusPin to GPIO output */
  	gpio_config(statusPin, 1);

  	/* set outputPin to GPIO output */
  	gpio_config(outputPin, 1);
  	/* set outputPin initial state to OFF */
  	gpio_write(outputPin, 0);

        /* set inputPin1 and inputPin2 to GPIO inputs */
	gpio_config(inputPin1, 0);
        gpio_config(inputPin2, 0);

	// Press Ctrl-C to exit the loop
	
    	puts("GPIO Input event detection loop is running ...");
  	while(1) {

    		gpio_write(statusPin, 1);

                /* press inputPin1 switch to turn ON LED outputPin */
    		if(gpio_read(inputPin1)){
			puts("turning ON outputPin ...");
      			gpio_write(outputPin, 1);
    		}
  
		/* press inputPin2 switch to turn OFF LED outputPin */
    		if(gpio_read(inputPin2)){
 			puts("turning OFF outputPin ...");
      			gpio_write(outputPin, 0);
    		}

                /* status LED will continously blink indicating the loop is running */
    		mswait(200);
    		gpio_write(statusPin, 0);
    		mswait(200);
 	}
}

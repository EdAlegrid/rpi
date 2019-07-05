/************************

   PWM Example

   Author: Ed Alegrid

*************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>

#include "./src/rpi.h"

/**
 * Circuit Setup
 *
 * Connect an LED to pin 13 (PHY Pin 33). 
 *
 */

/* output pin to generate a pulse */
uint8_t pin = 13;

int count = 0;

/* pwm setup */
void pwm(uint8_t pin){

        /* reset to input */
  	pwm_reset_pin(pin);

  	puts("generating a pulse ...");

        /* set pin 13 to alt-func 0, depends on the pin number */
  	pwm_set_pin(pin);
 
  	pwm_set_clock_freq(192);	// set clock freq to 10 KHz or 0.1 ms time resolution
    	mswait(25);

  	pwm_enable(pin, 1);		// enable PWM
  	pwm_set_mode(pin, 1);		// use Mark/Space
  	//pwm_set_pola(pin, 1);		// reverse duty cycle (pw/T)

  	pwm_set_range(pin, 1000);	// set Period T of the pulse
  	pwm_set_data(pin, 100);		// set pw of the pulse

  	mswait(2000);

  	pwm_reset_pin(pin); 		// reset pin 13 to input from alt-func 0   
}

/* Ctrl-C handler */
void sighandler(int signum)
{
   	printf("\nsighandler invoked %d, exiting ...\n", signum);
	
	pwm_reset_pin(pin); 
        
        puts("closing rpi ...");
   	rpi_close();
   	exit(1);
}

/************

    main

*************/
int main(){
 
	signal(SIGINT, sighandler);
 
    	rpi_init();
 
  	puts("starting pwm loop operation ...");
  	while(1) {

		count++;

		pwm(pin);

		mswait(2000);

                if(count == 3){
			exit(0);
                }
	}
}

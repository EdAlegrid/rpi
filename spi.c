/************************

   SPI Example

   Author: Ed Alegrid

************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>

#include "./src/rpi.h"

/**
 * Circuit Setup
 *
 * Connect the spi MCP2008 chip to RPi based on the datasheet. 
 * We will use chip select 0 line to connect with the MCP2008 chip.
 * VDD and Vref are connected to Raspberry Pi 3.3 V.
 * Channel 0 (pin 1) will be used for analog input voltage using single-ended mode. 
 * Since Vref is set to 3.3 V, max. analog input voltage
 * should not be greater than 3.3 V.
 */

/* spi read buffer */
char rbuf[16]; 
	
/* spi write buffer */
char wbuf[16];

/* ambient temperature reading based on datasheet */
void mcp2008(void){

	/* start spi operation */ 
	spi_start();

        puts("\n*** SPI MCP2008 A/D ***");

        /* set data transfer speed */ 
        spi_set_clock_freq(2500); //100 kHz
	
	spi_set_data_mode(0);

	spi_set_chip_select_polarity(0, 0);

	/* select MCP23017 slave device */
        spi_chip_select(0);
  
        /* access config register */
  	wbuf[0] = 0x01; // 16 bit register
  	wbuf[1] = 0x80; // MSB upper byte
  	wbuf[2] = 0x00; // LSB lower byte

        /* write 3 bytes of data to config register */
        spi_write(wbuf, 3);

	/* read 3 bytes of data from slave device */
        spi_read(rbuf, 3); 

        int data1 = rbuf[1] << 8; 	// need 2 bits data
        int data2 = rbuf[2];		// full 8 bits needed
        int value = data1 + data2;	// combine to get 10 bit result

   	for(int i = 0; i< 3; i++){
    		printf("spi rbuf[%d] %x\n", i, rbuf[i]); 
    
    	}
       
	printf("* A/D digital code: %i\n", value); 

        /* compute the output voltage */ 
	float vout = (float)((value * 3.3)/1024);
        
	printf("* A/D voltage output: %f\n", vout); 

	spi_stop();
}

/* Ctrl-C handler */
void sighandler(int signum)
{
   	printf("\nsighandler invoked %d, exiting ...\n", signum);
	
	spi_stop();
        
        puts("closing rpi ...");
   	rpi_close();
   	exit(1);
}

/************

    main

*************/
int main(void){
 
	signal(SIGINT, sighandler);
  
    	rpi_init();
 
  	puts("starting spi loop operation ...");
  	while(1) {
		mcp2008();
                mswait(2000);
	}
}
  

/************************

   I2C Example

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
 * Connect the i2c MCP9808 chip to RPi using pins GPIO02/GPIO03 (pin 03/05). 
 *
 * We will use the default slave address of 0x18.
 */

/* i2c read buffer */
char rbuf[16]; 
	
/* i2c write buffer */
char wbuf[16];

/* read ambient temperature based on datasheet */
int8_t getTemp(void){

        float Temp;
	
        /* get temp reading from ambient register */
        int UpperByte = rbuf[0]; // READ 8 bits 
        float LowerByte = rbuf[1];
 
        /* Convert the temperature data */
	UpperByte = UpperByte & 0x1F;	 // Clear flag bits

	// TA < 0°C
	if ((UpperByte & 0x10) == 0x10){
		UpperByte = UpperByte & 0x0F; // Clear SIGN
		Temp = 256 - ((UpperByte * 16) + ((float)(LowerByte/16)));

	}
	// TA > 0°C	
	else {
                float lb = (LowerByte/16);
 		Temp = ((UpperByte * 16) + lb);
	}
       
        printf("* Temp: %f C\n", Temp);

        return Temp;
}

void monitor_temp(void){
	
	puts("\nMonitor temp every 2 secs ...");
	
	/* access config register */ 
        wbuf[0] = 0x01;  	// address of config register
        wbuf[1] = 0x00;  	// MSB data
        wbuf[2] = 0x00;  	// LSB data 
        i2c_write(wbuf, 3);     // select config register
  
        /* read content of config register */
        i2c_read(rbuf, 2);	// read 2 bytes of data

        for(int i = 0; i< 2; i++){
    		printf("rbuf[%d] %x\n", i, rbuf[i]); 
    	}
	
        /* access ambient temp register */ 
        wbuf[0] = 0x05;		// address of ambient temp register
        i2c_write(wbuf,1);	// select ambient temp register 
   
        /* read content of temp register */
       	i2c_read(rbuf, 2);	// read 2 bytes of data

    	for(int i = 0; i< 2; i++){
    		printf("rbuf[%d] %x\n", i, rbuf[i]);
    	}

	/* get temperature data based on datasheet */
        getTemp();
        
    	mswait(2000);
	 
    	/* stop i2c operation */
    	i2c_stop();

}

/* Ctrl-C handler */
void sighandler(int signum)
{
   	printf("\nsighandler invoked %d, exiting ...\n", signum);
	
	i2c_stop();
        
        puts("closing rpi ...");
   	rpi_close();
   	exit(1);
}

/************

    main

*************/
int main(void){
 
	signal(SIGINT, sighandler);
  
	/* initialize rpi library */ 
    	rpi_init(1);
	
	/* start i2c operation, SDA and SCL pins setup */ 
	i2c_start();
	
	/* access temp sensor device */   
    	i2c_select_slave(0x18);
 
        /* set data transfer speed */ 
	i2c_data_transfer_speed(400000); // 400 kHz
 
  	puts("*** Monitor Ambient Temp Using I2C MCP9808 ***");
	
  	while(1) {
		monitor_temp();
                mswait(2000);
	}
}

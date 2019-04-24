/** @file
    spi.c
   
  * @brief description
    implementation of an Serial Periphral Interface (SPI) device driver for TM4C123 including 
	the following routines:
	- device initialization.
	- SPI ISR, if required.
	
  * @author
    Abdulmaguid Eissa

  * @date
    Aoril 19, 2019

  *	@COPYRIGHT NOTICE
    (2019)
  *
  *
  *
* */

#include <stdint.h>

#include "tm4c123gh6pm.h"
#include "spi.h"
#include "port.h"
#include "main.h"




// ************* spi_init **************
void
SPI_init(void) {
	volatile uint32_t delay;
	SPI_MODULE_R   |= SSI_MODULE0_EN;
	GPIO_CLOCK_R   |= PORTA_CLOCK_EN;
	delay           = GPIO_CLOCK_R;
	// GPIO initializations
	GPIO_DIR_R     |= PORTA_OUT_DIR;
	GPIO_ALTF_R    |= PORTA_SSI_SETUP;
	GPIO_DIGITAL_R |= PORTA_DIO_EN;
	GPIO_PCTRL_R   &= (PORTA_CTRL_CLR | PORTA_SSI_EN);
	// SSI initializations
	SPI_CONTROL_R  &= ~SSI_CONTROL_EN;                    // Disable SSI while configuration
	SPI_CONTROL_R   = (SPI_CONTROL_R&~SSI_MASTER_MOD);     // Enable SSI master mode
	SPI_CLK_CGR_R  &= ~SSI_CLK_SRC;                       // Configure system clock
	SPI_CLK_PRS_R  &= (~SSI_CPRS_CPSDVSR | SSI_CPDVSR_24);  // Configure for 24 divisor
	SPI_SETUP_R    &= ~(SSI_CR_SCR |                         // SCR = 0, SERIAL CLOCK RATE
		SSI_CR_SPH |                         // SPH = 0, SERIAL CLOCK PHASE
		SSI_CR_SPO);                        // SPO = 0, SERIAL CLOCK POLARITY 
	SPI_SETUP_R    &= (~SSI_CR_FRF | SSI_CR_FSSPI);           // FRF = 0, FREE SCALE SPI
	SPI_SETUP_R    &= (~SSI_CR_DSS | SSI_CR_DSS_8);           // DSS = 0x7, DATA SIZE SELECT
	SPI_CONTROL_R  |= SSI_CONTROL_EN;                     // Enable SSI after setting up.
}



// ************* end of file *************

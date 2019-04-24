/** @file
    adc.c
 
  * @brief description
    implementation of an Analog to Digital Conversion (ADC) device driver for TM4C123 including 
	the following routines:
	- device initialization.
	- ADC ISR, if required.
	- data getter from the ADC register.
	- digital data conversion.

  * @author
    Abdulmaguid Eissa.

  * @date
    April 18, 2019.

  *	@COPYRIGHT NOTICE
    (2019)
  *
  *
  *
* */

#include <stdint.h>

#include "tm4c123gh6pm.h"
#include "adc.h"
#include "port.h"
#include "main.h"


// ************* adc_init **************
void
ADC_init(void) {
	volatile uint32_t delay;
	ADC_MODULE_R   |= ADC_MODULE0_EN;
	GPIO_CLOCK_R   |= PORTE_CLOCK_EN;
	delay           = GPIO_CLOCK_R;
	// GPIO initialations
	GPIO_ALTF_R    |= PORTE_ADC_SETUP;    // Enable alternate function
	GPIO_DIGITAL_R &= ~PORTE_DIO_EN;   // Disable Digital IO
	GPIO_ANALOGF_R |= PORTE_ANLG_MOD;  // Enable analog function
	GPIO_DIR_R     &= ~PORTE_OUT_DIR;      // Configure for input pins
	// ADC initialitions
	ADC_SSPRI_R    |= ADC_SS3_HIPRI;      // Set sample sequencer 3 the highest
	ADC_ACTSS_R    &= ~ADC_ACTSS_EN;      // Disable SS3 while configuration
	ADC_EMUX_R     &= ~ADC_SW_TRG;         // Set SS3 for software trigger event.
	ADC_SSMUX3_R   &= ~ADC_SSMUX3_SIS;   // SS3 MUX3 sample input select
	ADC_SSCTRL3_R  |= ADC_IE0_END0;     // Configure END0 and IE0
	ADC_ACTSS_R    |= ADC_ACTSS_EN;       // Enable SS3 
}



// ************* adc_data_get **************
uint32_t
ADC_data_get(void) {
	uint32_t result = 0;

	ADC_PSSI_R |= ADC_SS3_INIT;                  // Initiate SS3
	while ((ADC_RINTS_R & ADC_SS3_IS) == 0) {};  // Wait for sampling to be done
	result = ADC_SSFIFO3_R;                      // Get the result from FIFO
	ADC_ISC_R |= ADC_SSIACK3;					 // Acknowledge the interrupt. 
	return (result);
}





// ************* adc_data_convert **************
// implementation of this function depends on the application.
// 12-bit ADC channel.
// Linear equation is A * (ADC data) >> 10 + B, where B is the offset
//                     A & B values are according to trial and error.
uint32_t
ADC_data_convert(uint32_t digital_samples) {
	return ((1228 * digital_samples) >> 10);
}





// ************* end of file *************

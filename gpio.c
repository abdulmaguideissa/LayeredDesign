/** @file
    gpio.c
   
  * @brief description
    implementation of the functions that define a GPIO

  * @author
    Abdulmaguid Eissa

  * @date
     April 22, 2019

  *	@COPYRIGHT NOTICE
  *
  *
  *
* */

#include <stdint.h>

#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "port.h"
#include "main.h"



// ************* GPIO_init **************
// PORTF 
void
GPIO_init(void) {
	volatile uint32_t delay;

	GPIO_CLOCK_R   |= GPIO_PF_CLK_EN;
	delay           = GPIO_CLOCK_R;
	GPIO_PF_CTRL_R &= ~GPIO_PF_CTRL_SET;
	GPIO_PF_ALTF_R &= ~GPIO_PORTF_PIN1;
	GPIO_PF_ALGF_R &= ~GPIO_PORTF_PIN1;
	GPIO_PF_DIR_R  |= GPIO_PORTF_PIN1;
	GPIO_PF_DEN_R  |= GPIO_PORTF_PIN1;
}







// ************* end of file *************

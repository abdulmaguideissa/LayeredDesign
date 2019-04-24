/** @file
    led.c
 
  * @brief description
    functions definitions of LEDs 
  
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

#include "led.h"
#include "gpio.h"
#include "port.h"
#include "main.h"

// ************* LED_init **************
void
LED_init(void) {
	GPIO_init();
}


// ************* LED_toggle **************
void
LED_toggle(void) {
	volatile uint8_t delay;

	for (delay = 0; delay < 256; delay++) {
		GPIO_PF_DATA_R ^= GPIO_PORTF_PIN1;
	}
}


// ************* LED_set **************
void
LED_set(void) {
	GPIO_PF_DATA_R |= GPIO_PORTF_PIN1
}


// ************* LED_clear **************
void
LED_clear(void) {
	GPIO_PF_DATA_R &= ~GPIO_PORTF_PIN1
}

















// ************* end of file *************

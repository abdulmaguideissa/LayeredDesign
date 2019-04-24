/** @file 
    led.h
    
  * @brief description
    APIs to interface LED functions implementations
   
  * @author
    Abdulmaguid Eissa

  * @date
    April 22, 2019

  *	@COPYRIGHT NOTICE 
  *
  *
  *
* */


#ifndef LED__H
#define LED__H


// ************* LED_init **************
// brief description: initializing the GPIO the LED attached to.
// inputs:   none
// outputs:  none
// NOTES:
void
LED_init(void);


// ************* LED_toggle **************
// brief description:  toggling the LED current state
// inputs:   none
// outputs:  none
// NOTES:
void
LED_toggle(void);


// ************* LED_set **************
// brief description:  set the LED to "ON"
// inputs:   none
// outputs:  none
// NOTES:
void
LED_set(void);


// ************* LED_clear **************
// brief description:  clear the LED to "OFF"
// inputs:   none
// outputs:  none
// NOTES:
void
LED_clear(void);

#endif  // ************* LED__H *************

        // ************* end of file *************

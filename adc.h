/** @file 
    adc.h

  * @brief description
    APIs to interface the ADC device driver.
	Every declaration is provided with decription, arguements clarification,
	outputs clarification.
	USER is meant to deal with these APIs, so the description is provided in this file
	and not in the source file.

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


#ifndef ADC__H
#define ADC__H


// ************* adc_init **************
// brief description: initializations of the ADC device.
// inputs:            none.
// outputs:           none.
// NOTES:
void
ADC_init(void);


// ************* adc_get **************
// brief description: ADC data getter after conversion of analog data into
//                    digital data
// inputs:    none.
// outputs:   12-bit digital result of conversion.
// NOTES:     resolution is 2^12 = 4095 different digital readings.
uint32_t 
ADC_data_get(void);


// ************* adc_data_convert **************
// brief description: converting the digital data into proper and useful data.
// inputs:    adc 12-bit data
// outputs:   meaningful data.
// NOTES:     implementation of this function depends on the application.
uint32_t
ADC_data_convert(uint32_t digital_samples);






#endif  // ************* ADC__H *************

        // ************* end of file *************

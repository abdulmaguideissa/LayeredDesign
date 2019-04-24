/** @file 
    main.h
    
  * @brief description
    A header file that contains common used values through project, gathered in one file
	for clarity, maintainability and for a value not to be confused with another value 
	or a definition.
	It also includes the registers values of the used devices/periphrals.
   
  * @author
    Abdulmaguid Eissa.

  * @date
    April 19, 2019

  *	@COPYRIGHT NOTICE
    (2019)
  *
  *
  *
* */


#ifndef MAIN__H
	#define MAIN__H


// *********************************************************
// ************************* GPIO **************************
// *********************************************************
// NOTE: Macros naming convension is according to the GPIO usge.
  // PORTE FOR ADC
#define PORTE_CLOCK_EN          (0x10)
#define PORTE_ANLG_MOD          (0x04)
#define PORTE_DIO_EN            (0x04)
#define PORTE_OUT_DIR           (0x04)
#define PORTE_ADC_SETUP         (0x04)
#define PORTE_CTRL_CLR          (0xFFFF00FF)
#define PORTE_ADC_EN            (0x00003300)
#define PORTE_ADC_OD            (0x08)

  // PORTA FOR SPI
#define PORTA_CLOCK_EN          (0x01)
#define PORTA_ALG_MOD           (0x03)
#define PORTA_DIO_EN            (0xEC)
#define PORTA_OUT_DIR           (0xC0)
#define PORTA_SSI_SETUP         (0x2C & (~0xC0))
#define PORTA_CTRL_CLR          (0xFF0F00FF)
#define PORTA_SSI_EN            (0x00202200)

  // POTRF FOR LED
#define GPIO_PORTF_PIN1         (0x02)
#define GPIO_PORTF_PIN2         (0x04)
#define GPIO_PORTF_PIN3         (0x08)
#define GPIO_PF_CLK_EN          (0x00000020)
#define GPIO_PF_CTRL_SET        (0x000000F0)




// *********************************************************
// ************************* ADC ***************************
// *********************************************************
// ADC assigned registers values, including ADC periphral
// values and its GPIO values.
#define SYSTEM_CLOCK            (80000000)
#define ADC_MODULE0_EN          (0x00000001)
#define ADC_SS3_HIPRI           (0x0123)
#define ADC_ACTSS_EN            (0x0008)
#define ADC_SW_TRG              (0xF000)
#define ADC_SSMUX3_SIS          (0x000F)
#define ADC_IE0_END0            (0x0006)
#define ADC_SS3_INIT            (0x0008)
#define ADC_SS3_IS              (0x08)
#define ADC_SSIACK3             (0x0008)
#define DATA_BYTE               (0xFF)
#define MAXTRIES                (5)


// *********************************************************
// ************************* SPI ***************************
// *********************************************************
#define CLOCK                   (80000000)
#define SSI_MODULE0_EN          (0x10)
#define SSI_MASTER_MOD          (0x04)
#define SSI_CONTROL_EN          (0x00000002)
#define SSI_CLK_SRC             (0x0000000F)                                 
#define SSI_CPRS_CPSDVSR        (0x000000FF)                                 
#define SSI_CPDVSR_24           (24)
#define SSI_CR_SCR              (0x0000FF00)
#define SSI_CR_SPH              (0x00000080)
#define SSI_CR_SPO              (0x00000040)
#define SSI_CR_FRF              (0x00000030)
#define SSI_CR_FSSPI            (0x00000000)
#define SSI_CR_DSS              (0x0000000F)
#define SSI_CR_DSS_8            (0x00000007)


// *********************************************************
// ******************** LCD commands ***********************
// *********************************************************
// Choose another value, starting from FUNCTION SET,
// according to operation
#define DC                      (*((volatile long_t *)0x40004100)) // PA6, CMD/DATA
#define RESET                   (*((volatile long_t *)0x40004200)) // PA7, RESET
#define RESET_LOW               (0)
#define RESET_HIGH              (0x80)
#define LCD_MAX_X               (84)
#define LCD_MAX_Y               (48)
#define LCD_COMMAND             (0)
#define LCD_DATA                (1)
#define BLANK                   (0x00)
#define X_POSITION              (0x80)
#define Y_POSITION              (0x40)
#define FUNCTION_SET            (0x21)
#define V_OPERATION             (0xB8)  
#define TEMP_COEFF              (0x04) 
#define BIAS_MOD                (0x14)
#define PRE_CTRL                (0x20)
#define DISP_CTRL               (0x0C) 


// *********************************************************
// ************************ LED ****************************
// *********************************************************
#define LED_BLUE                (GPIO_PORTF_PIN1)




#endif  // ************* MAIN__H *************

        // ************* end of file *************

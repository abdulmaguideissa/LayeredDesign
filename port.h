/** @file 
    port.h
    
  * @brief description 
    A header file that contains all of the ports register definitions used in the project 
	devices/periphrals, organized in generic definitions- independent from the
	manufacturer definitions- to be used easly in other projects.
	Device/periphral section will be associated with its GPIO definitions that are required 
	in the initializations.
   
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


#ifndef PORT__H
	#define PORT__H

// *********************************************************
// ************************ GPIO ***************************
// *********************************************************
// NOTE : Macros naming convension is according to the GPIO usge.
#ifndef GPIO_CLOCK_R 
	#define GPIO_CLOCK_R             (SYSCTL_RCGC2_R)
#endif // !GPIO_CLOCK_R 

  // PORTE FOR ADC
#define GPIO_PCTRL_R             (GPIO_PORTE_PCTL_R)
#define GPIO_ANALOGF_R           (GPIO_PORTE_AMSEL_R)
#define GPIO_ALTF_R              (GPIO_PORTE_AFSEL_R)
#define GPIO_DIGITAL_R           (GPIO_PORTE_DEN_R)
#define GPIO_DIR_R               (GPIO_PORTE_DIR_R)
#define GPIO_DATA_R              (GPIO_PORTE_DATA_R)
#define GPIO_ODEN_R              (GPIO_PORTE_ODR_R)

  // PORTA FOR SPI
#define GPIO_PCTRL_R             (GPIO_PORTA_PCTL_R)
#define GPIO_ALG_FN_R            (GPIO_PORTA_AMSEL_R)
#define GPIO_ALTF_R              (GPIO_PORTA_AFSEL_R)
#define GPIO_DIGITAL_R           (GPIO_PORTA_DEN_R)
#define GPIO_DIR_R               (GPIO_PORTA_DIR_R)
#define GPIO_DATA_R              (GPIO_PORTA_DATA_R)

  // PORTF FOR LED
#define GPIO_PF_DATA_R           (GPIO_PORTF_DATA_R)
#define GPIO_PF_CTRL_R           (GPIO_PORTF_PCTL_R)
#define GPIO_PF_ALTF_R           (GPIO_PORTF_AFSEL_R)
#define GPIO_PF_ALGF_R           (GPIO_PORTF_AMSEL_R)
#define GPIO_PF_DIR_R            (GPIO_PORTF_DIR_R)
#define GPIO_PF_DEN_R            (GPIO_PORTF_DEN_R)


// *********************************************************
// ************************* ADC ***************************
// *********************************************************
// NOTE: Using the ADC channel associated with PORTE
//       that is different from the GPIO to be used for 
//       other purposes, such as SPI or pure GPIO.
#define ADC_MODULE_R             (SYSCTL_RCGC0_R)      // ADC module select
#define ADC_SSPRI_R              (ADC0_SSPRI_R)        // Sample sequencer priority
#define ADC_ACTSS_R              (ADC0_ACTSS_R)        // Action on sample sequencer
#define ADC_EMUX_R               (ADC0_EMUX_R)         // 
#define ADC_SSMUX3_R             (ADC0_SSMUX3_R)
#define ADC_SSCTRL3_R            (ADC0_SSCTL3_R)
#define ADC_SSFIFO3_R            (ADC0_SSFIFO3_R)
#define ADC_PSSI_R               (ADC0_PSSI_R)
#define ADC_ISC_R                (ADC0_ISC_R)
#define ADC_RINTS_R              (ADC0_RIS_R)
#define ADC_INT_MSK_R            (ADC0_IM_R)


// *********************************************************
// ************************* SPI ***************************
// *********************************************************
// Example on SPI MODULE 0 in TM4C123GH6PM 
#define SPI_MODULE_R             (SYSCTL_RCGC1_R)
#define SPI_CLK_CGR_R            (SSI0_CC_R )                            
#define SPI_CONTROL_R            (SSI0_CR1_R)
#define SPI_CLK_PRS_R            (SSI0_CPSR_R)
#define SPI_SETUP_R              (SSI0_CR0_R)
#define SPI_STATUS_R             (SSI0_SR_R)
#define SPI_DATA_R               (SSI0_DR_R)
#define SPI_RINTS_R              (SSI0_RIS_R)
#define SPI_MINTS_R              (SSI0_MIS_R)
#define SPI_INT_MSK_R            (SSI0_IM_R)
#define SPI_INT_CLR_R            (SSI0_ICR_R)
#define SPI_DMA_CTRL_R           (SSI0_DMACTL_R)




#endif  // ************* PORT__H *************

        // ************* end of file *************

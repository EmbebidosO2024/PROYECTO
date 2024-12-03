#include "PWM.h"

/**
 * @brief Initializes the PWM module.
 *
 * Configures the FlexTimer Module (FTM0) to generate PWM signals for controlling motors or servos.
 * Sets up the required clock and pin configurations for PWM operation.
 */
void PWM_INIT(void) {
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam[2];

    /* Enable the clock for FTM0 and PORTD */
    SIM->SCGC6 |= (1 << 24);  /**< Enable clock for FTM0 */
    SIM->SCGC5 |= (1 << 12);  /**< Enable clock for PORTD */

    /* Disable write protection for FTM0 */
    FTM0->MODE |= (1 << 2);

    /* Set up the timer counter settings */
    FTM0->SC = 0xD;           /**< Select clock source and prescaler */
    FTM0->MOD = 37500;        /**< Set the modulo value for a 50Hz PWM frequency */

    /* Configure channel 4 of FTM0 for PWM */
    FTM0->CONTROLS[4].CnSC = 0b101000; /**< Set channel mode to Edge-Aligned PWM */
    FTM0->CONTROLS[4].CnV = 2812;      /**< Initialize with a 7.5% duty cycle (neutral position) */

    /* Configure channel 5 of FTM0 for PWM */
    FTM0->CONTROLS[5].CnSC = 0b101000; /**< Set channel mode to Edge-Aligned PWM */
    FTM0->CONTROLS[5].CnV = 2812;      /**< Initialize with a 7.5% duty cycle (neutral position) */

}

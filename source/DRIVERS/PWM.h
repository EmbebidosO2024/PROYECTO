#ifndef DRIVERS_PWM_H_
#define DRIVERS_PWM_H_

#include "fsl_ftm.h"

/* FlexTimer (FTM) configuration */

/**
 * @brief Base address of the FlexTimer Module (FTM) used.
 *
 * FTM0 is used for generating PWM signals for controlling motors or servos.
 */
#define BOARD_FTM_BASEADDR       FTM0

/**
 * @brief Channel numbers used for PWM generation.
 *
 * BOARD_FIRST_FTM_CHANNEL is used for motor control.
 * BOARD_SECOND_FTM_CHANNEL is used for servo control.
 */
#define BOARD_FIRST_FTM_CHANNEL  5U /**< Channel 5 of FTM0 */
#define BOARD_SECOND_FTM_CHANNEL 4U /**< Channel 4 of FTM0 */

/* Clock configuration for the FTM driver */

/**
 * @brief Source clock frequency for the FTM driver.
 *
 * Retrieves the clock frequency from the Bus Clock source for configuring FTM.
 */
#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

/* PWM signal level configuration */

/**
 * @brief PWM output polarity configuration.
 *
 * Configures the active PWM signal level. Default is High True.
 */
#ifndef FTM_PWM_ON_LEVEL
#define FTM_PWM_ON_LEVEL kFTM_HighTrue
#endif

/**
 * @brief PWM signal frequency.
 *
 * Configures the PWM frequency to 50Hz, typically used for servos and motor ESCs.
 */
#ifndef DEMO_PWM_FREQUENCY
#define DEMO_PWM_FREQUENCY (50u)
#endif

/* Duty cycle ranges for PWM mapping */

/**
 * @brief Duty cycle range for motor control.
 *
 * These values correspond to specific pulse widths required for controlling motors.
 */
#define DUTY_CYCLE_MIN_DC 2300 /**< Minimum duty cycle for motor */
#define DUTY_CYCLE_MAX_DC 3100 /**< Maximum duty cycle for motor */

/**
 * @brief Duty cycle range for servo control.
 *
 * These values correspond to specific pulse widths required for controlling servos.
 */
#define DUTY_CYCLE_MIN_SERVO 1875 /**< Minimum duty cycle for servo */
#define DUTY_CYCLE_MAX_SERVO 3749 /**< Maximum duty cycle for servo */

/* Function prototypes */

/**
 * @brief Initializes the PWM module.
 *
 * Configures the FlexTimer Module (FTM0) to generate PWM signals on specified channels.
 * Sets up clocks, modes, and initial duty cycles.
 */
void PWM_INIT(void);

#endif /* DRIVERS_PWM_H_ */

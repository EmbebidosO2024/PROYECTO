

#ifndef DRIVERS_UART_H_
#define DRIVERS_UART_H_

#include "fsl_uart.h"

/* UART instance and settings */
#define DEMO_UART            UART1                   /**< UART instance used for communication */
#define DEMO_UART_CLK_FREQ   CLOCK_GetFreq(kCLOCK_CoreSysClk) /**< Clock frequency for UART */
#define DEMO_UART_IRQn       UART1_RX_TX_IRQn        /**< UART interrupt number */
#define DEMO_UART_IRQHandler UART1_RX_TX_IRQHandler  /**< UART interrupt handler */

/* Buffer and channel definitions */
#define DEMO_RING_BUFFER_SIZE 32 /**< Size of the ring buffer for storing received data */
#define NUM_CHANNELS          8  /**< Number of channels used in the communication protocol */

/* External variables shared between the UART driver and other modules */
extern uint8_t demoRingBuffer[DEMO_RING_BUFFER_SIZE]; /**< Ring buffer for incoming UART data */
extern volatile uint16_t rxIndex;                    /**< Current index for writing into the buffer */
extern uint16_t channelValues[NUM_CHANNELS];         /**< Array to store values for the 8 communication channels */

/**
 * @brief Maps an input value from one range to another.
 *
 * This function is used to scale a value from an input range to an output range.
 * It performs a linear transformation of the input value to fit within the output range.
 *
 * @param value The input value to be mapped.
 * @param inMin The lower bound of the input range.
 * @param inMax The upper bound of the input range.
 * @param outMin The lower bound of the output range.
 * @param outMax The upper bound of the output range.
 * @return float The scaled value within the output range.
 */
float mapValue(uint16_t value, uint16_t inMin, uint16_t inMax, float outMin, float outMax);

/**
 * @brief Initializes the UART module.
 *
 * This function configures the UART hardware with predefined settings such as
 * baud rate and enables the interrupt for receiving data. It is essential for
 * setting up UART communication in the system.
 */
void UART_INIT(void);

#endif /* DRIVERS_UART_H_ */



#include "UART.h"

/* Buffer to store incoming UART data */
uint8_t demoRingBuffer[DEMO_RING_BUFFER_SIZE];

/* Index for tracking the buffer position */
volatile uint16_t rxIndex = 0;

/* Array to store channel values from UART data */
uint16_t channelValues[NUM_CHANNELS] = {0};

/**
 * @brief Initializes the UART module.
 *
 * Configures UART1 to receive data using the iBus protocol at 115200 baud rate.
 * Enables the UART interrupt for receiving data.
 */
void UART_INIT(void) {
    uart_config_t config;

    /* Enable the clock for UART1 */
    SIM->SCGC4 = SIM->SCGC4 | (1 << 11);

    /* Get the default UART configuration */
    UART_GetDefaultConfig(&config);

    /* Set UART baud rate to 115200 (for iBus protocol) */
    config.baudRate_Bps = 115200;
    config.enableTx = false; /* Disable transmission */
    config.enableRx = true;  /* Enable reception */

    /* Initialize UART1 with the specified configuration */
    UART_Init(DEMO_UART, &config, DEMO_UART_CLK_FREQ);

    /* Enable UART1 receive data full interrupt */
    UART_EnableInterrupts(DEMO_UART, kUART_RxDataRegFullInterruptEnable);

    /* Enable UART1 interrupt in the NVIC (Nested Vector Interrupt Controller) */
    EnableIRQ(DEMO_UART_IRQn);
}

/**
 * @brief Maps a value from one range to another.
 *
 * This function converts an input value from a specified input range to a corresponding
 * value in a target output range. The mapping is performed linearly.
 *
 * @param value The input value to be mapped.
 * @param inMin The lower bound of the input range.
 * @param inMax The upper bound of the input range.
 * @param outMin The lower bound of the output range.
 * @param outMax The upper bound of the output range.
 * @return float The mapped value in the output range.
 */
float mapValue(uint16_t value, uint16_t inMin, uint16_t inMax, float outMin, float outMax) {
    return ((float)(value - inMin) * (outMax - outMin)) / (float)(inMax - inMin) + outMin;
}


#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_ftm.h"
#include "fsl_uart.h"
#include "fsl_debug_console.h"
#include <stdint.h>
#include "DRIVERS/UART.h"
#include "DRIVERS/PWM.h"

/**
 * @brief UART1 Interrupt Handler
 *
 * This function is triggered when UART1 receives data. It processes the received
 * data, validates the protocol header, extracts channel values, and updates the
 * PWM duty cycles accordingly.
 */
void DEMO_UART_IRQHandler(void)
{
    uint8_t data;

    /* Check if the UART receive data register is full */
    if ((kUART_RxDataRegFullFlag) & UART_GetStatusFlags(DEMO_UART))
    {
        /* Read the received byte */
        data = UART_ReadByte(DEMO_UART);

        /* Store the received byte in the ring buffer if there's space */
        if (rxIndex < DEMO_RING_BUFFER_SIZE)
        {
            demoRingBuffer[rxIndex++] = data;

            /* Check and align the buffer to the protocol header */
            if (rxIndex >= 2 && demoRingBuffer[0] != 0x20 && demoRingBuffer[1] != 0x40)
            {
                /* Shift the buffer to resynchronize with the header */
                for (int i = 1; i < rxIndex; i++)
                {
                    demoRingBuffer[i - 1] = demoRingBuffer[i];
                }
                rxIndex--;
            }

            /* Process the complete data frame (32 bytes) */
            if (rxIndex == DEMO_RING_BUFFER_SIZE)
            {
                rxIndex = 0; /* Reset buffer index */

                /* Validate the protocol header */
                if (demoRingBuffer[0] == 0x20 && demoRingBuffer[1] == 0x40)
                {
                    /* Extract channel values from the data frame */
                    for (int i = 0; i < NUM_CHANNELS; i++)
                    {
                        channelValues[i] = demoRingBuffer[2 + i * 2] | (demoRingBuffer[3 + i * 2] << 8);
                    }

                    /* Map channel values to PWM duty cycles */
                    float dutyCycle1 = mapValue(channelValues[1], 1000, 2000, DUTY_CYCLE_MIN_DC, DUTY_CYCLE_MAX_DC);
                    float dutyCycle2 = mapValue(channelValues[3], 1000, 2000, DUTY_CYCLE_MAX_SERVO, DUTY_CYCLE_MIN_SERVO);

                    /* Update PWM registers */
                    FTM0->CONTROLS[4].CnV = dutyCycle1;
                    FTM0->CONTROLS[5].CnV = dutyCycle2;

                    /* Trigger a software update for PWM */
                    FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR, true);
                }
                else
                {
                    PRINTF("Invalid header\r\n");
                }
            }
        }
    }

    SDK_ISR_EXIT_BARRIER;
}

/**
 * @brief Main function
 *
 * Initializes the board hardware, UART, and PWM modules. The system continuously
 * processes incoming UART data in the background and updates PWM signals accordingly.
 *
 * @return int This function never returns.
 */
int main(void)
{
    /* Initialize board pins and clock configurations */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();

    /* Initialize UART and PWM modules */
    UART_INIT();
    PWM_INIT();

    /* Infinite loop */
    while (1)
    {
        /* Main loop is intentionally empty as all processing is handled in interrupts */
    }
}

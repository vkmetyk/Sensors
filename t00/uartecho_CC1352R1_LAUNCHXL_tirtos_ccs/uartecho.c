#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Driver configuration */
#include "ti_drivers_config.h"


#define STRING_SIZE 256
#define ERROR 1

int string_realloc(UART_Handle uart, char **str, size_t *pos, size_t *size);

void *mainThread(void *arg0)
{
    const char  echoPrompt[] = "Echoing characters:\r\n";
    UART_Handle uart;
    UART_Params uartParams;

    /* Call driver init functions */
    GPIO_init();
    UART_init();

    /* Configure the LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_TEXT;
    uartParams.readDataMode = UART_DATA_TEXT;
    uartParams.readReturnMode = UART_RETURN_NEWLINE;
    uartParams.baudRate = 115200;

    uart = UART_open(CONFIG_UART_0, &uartParams);

    if (uart == NULL) {
        /* UART_open() failed */
        while (1);
    }

    /* Turn on user LED to indicate successful initialization */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    UART_write(uart, echoPrompt, sizeof(echoPrompt));

    size_t size = STRING_SIZE;
    size_t pos = 0;
    char *input = malloc(2);

    if (input == NULL) {
        UART_write(uart, "Malloc error\n", 13);
    } else {
        while (1) {
            UART_read(uart, input + pos, 1);
            if (*(input + pos) == '\n' || *(input + pos) == '\r' || *(input + pos) == 10) {
                UART_write(uart, input, pos + 1);
                UART_write(uart, "\n", 1);
                pos = 0;
            }
            else if (pos + 1 > size) {
                if (string_realloc(uart, &input, &pos, &size) == ERROR)
                    return NULL;
            }
            else {
                pos++;
            }
        }
    }
    return NULL;
}

int string_realloc(UART_Handle uart, char **str, size_t *pos, size_t *size) {
    if ((*str = realloc(*str, *size + 256)) == NULL) {
        if ((*str = realloc(*str, STRING_SIZE)) == NULL) {
            UART_write(uart, "\nRealloc fatal error", 20);
            return ERROR;
        }
        else {
            UART_write(uart, "\nMax input size, please try again.\n", 35);
            *size = STRING_SIZE;
            *pos = 0;
        }
    }
    else {
        *size += STRING_SIZE;
    }
    return 0;
}

/**
 * main.c
 */

#include <stdint.h>
#include "tm4c1294ncpdt.h"

int main(void)
{
    // Turn on GPIO-F and -N blocks
    SYSCTL_RCGCGPIO_R = 0x1020;

    // Enable pins 0-1 of GPIO-N and set to output
    GPIO_PORTN_DIR_R = 0x03;
    GPIO_PORTN_DEN_R = 0x03;

    // Enable pins 0 & 4 of GPIO-F and set to output
    GPIO_PORTF_DIR_R = 0x11;
    GPIO_PORTF_DEN_R = 0x11;

    while(1) {
        // Recall that bits 9:2 of address act as mask
        // for bits 7:0 of DATA. Yes, it's weird, but
        // it is abstracted now.
        GPIO_PORTN_DATA_R = 0x02;
        GPIO_PORTF_DATA_R = 0x10;

        volatile int counter = 0;
        while (counter < 1000000) {
            ++counter;
        }

        GPIO_PORTN_DATA_R = 0x01;
        GPIO_PORTF_DATA_R = 0x01;

        counter = 0;
        while (counter < 1000000) {
            ++counter;
        }
    }

    //	return 0;
}

/**
 * main.c
 */

#include <stdint.h>
#include "tm4c1294ncpdt.h"

#define D1 (1U << 1)
#define D2 (1U << 0)
#define D3 (1U << 4)
#define D4 (1U << 0)

void delay(int iter);

void delay(int iter) {
    volatile int counter = 0;
    while (counter < iter) {
        ++counter;
    }
}

int main(void)
{
    /* Note that the version of the processor header
     * file I am using (tm4c1294ncpdt.h) was retrieved
     * from users.ece.utexas.edu/~valvano/arm/ and
     * has been modified to use AHB GPIO addresses by
     * default, with the non-AHB names kept, but the
     * AHB addresses used where applicable. This is why
     * the code below looks different from that in the
     * course video.
     */

    // Turn on GPIO-F and -N blocks
    SYSCTL_RCGCGPIO_R = 0x1020;

    // Enable pins 0-1 of GPIO-N and set to output
    GPIO_PORTN_DIR_R |= (D1 | D2);
    GPIO_PORTN_DEN_R |= (D1 | D2);

    // Enable pins 0 & 4 of GPIO-F and set to output
    GPIO_PORTF_DIR_R |= (D3 | D4);
    GPIO_PORTF_DEN_R |= (D3 | D4);

    while(1) {
        // Recall that bits 9:2 of address act as mask
        // for bits 7:0 of DATA. Yes, it's weird, but
        // it is abstracted now.
        GPIO_PORTN_DATA_BITS_R[D1 | D2] = D1;
        GPIO_PORTF_DATA_BITS_R[D3 | D4] = D3;

        delay(1e6);

        GPIO_PORTN_DATA_BITS_R[D1 | D2] = D2;
        GPIO_PORTF_DATA_BITS_R[D3 | D4] = D4;

        delay(1e6);
    }

    //	return 0;
}

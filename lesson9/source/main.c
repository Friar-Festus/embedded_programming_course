/**
 * main.c
 */

#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "delay.h"

#define D1 (1U << 1)
#define D2 (1U << 0)
#define D3 (1U << 4)
#define D4 (1U << 0)

unsigned fact(unsigned n);

int main(void)
{
    unsigned volatile x;

    x = fact(0U);
    x = 2U + 3U * fact(1U);
    x = fact(5U);
    (void)fact(5U);

    delay(x);

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

unsigned fact(unsigned n) {
    // 0! = 1
    // n! = n*(n-1)! for n > 0

    unsigned foo[10];
    foo[n] = n;

    if (n == 0U) {
        return 1U;
    }
    else {
        return foo[n] * fact(n - 1U);
    }
}

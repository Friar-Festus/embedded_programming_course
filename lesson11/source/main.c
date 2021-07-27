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

uint8_t u8a, u8b;
uint16_t u16c, u16d;
uint32_t u32e, u32f;

int8_t s8;
int16_t s16;
int32_t s32;

int main(void)
{
    u8a = sizeof(u8a);
    u16c = sizeof(uint16_t);
    u32e = sizeof(uint32_t);

    u8a = 0xa1;
    u16c = 0xc1c2;
    u32e = 0xe1e2e3e4;

    u8b = u8a;
    u16d = u16c;
    u32f = u32e;

    u16c = 40000U;
    u16d = 30000U;
    u32e = (uint32_t) u16c + (uint32_t) u16d;

    u16c = 100U;
    s32 = 10 - u16c;

    if ((int32_t) u32e > -1) {
        u8a = 1;
    }
    else {
        u8a = 0;
    }

    u8a = 0xFFU;
    if ((uint8_t) (~u8a) == 0x00U) {
        u8b = 1U;
    }

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

        delay(5e5);

        GPIO_PORTN_DATA_BITS_R[D1 | D2] = D2;
        GPIO_PORTF_DATA_BITS_R[D3 | D4] = D4;

        delay(5e5);
    }

    //	return 0;
}

unsigned fact(unsigned n) {
    // 0! = 1
    // n! = n*(n-1)! for n > 0

    unsigned foo[10]; // Changing to 100 will result in stack overflow
    foo[n] = n;

    if (n == 0U) {
        return 1U;
    }
    else {
        return foo[n] * fact(n - 1U);
    }
}

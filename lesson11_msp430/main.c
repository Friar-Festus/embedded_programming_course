#include <stdint.h>
#include <msp430.h> 

#define LED1 (1U << 0)
#define LED2 (1U << 6)
/**
 * main.c
 */

uint8_t u8a, u8b;
uint16_t u16c, u16d;
uint32_t u32e, u32f;

int8_t s8;
int16_t s16;
int32_t s32;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

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

    u16c = 100U;
    s32 = 10 - (int16_t) u16c; // Could also cast to int32_t, but unnecessary in this case

    /* As stated in the video, only one of the right-hand
     * operands needs to be explicitly cast to the
     * largest expected left-hand result, but I think it
     * makes sense to promote all of them explicitly. */
    u32e = (uint32_t) u16c + (uint32_t) u16d;

    P1DIR |= (LED1 | LED2);

    while (1) {
        unsigned volatile i;
        P1OUT |= LED1;
        P1OUT &= ~LED2;
        for (i = 20000U; i != 0U; --i) {
            // spin wheels
        }

        P1OUT &= ~LED1;
        P1OUT |= LED2;
        for (i = 20000U; i != 0U; --i) {
            // spin wheels
        }
    }
}

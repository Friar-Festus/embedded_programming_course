/**
 * main.c
 */

#include <stdint.h>
//#include "tm4c_cmsis.h"
#include "tm4c1294ncpdt_cmsis.h"
#include "delay.h"

#define D1 (1U << 1)
#define D2 (1U << 0)
#define D3 (1U << 4)
#define D4 (1U << 0)

typedef struct {
    uint8_t y;
    uint16_t x;
} Point;
//__attribute__((packed)) Point; // avoid packed structs unless absolutely necessary.

typedef struct {
    Point top_left;
    Point bottom_right;
} Window;

typedef struct {
    Point corners[3];
} Triangle;

Window w, w2;
Triangle t;

Point p1;
Point p2;

int main(void) {
    Point *pp;
    Window *wp;

    p1.x = sizeof(Point);
    p1.y = 0xAAU;

    w.top_left.x = 1U;
    w.bottom_right.y = 2U;

    t.corners[0].x = 1U;
    t.corners[2].y = 2U;

    p2 = p1;
    w2 = w;

    pp = &p1;
    wp = &w2;

    (*pp).x = 1U;
    (*wp).top_left = *pp;

    pp->x = 1U;
    wp->top_left = *pp;

    // Turn on GPIO-F and -N blocks
    SYSCTL->RCGCGPIO |= 0x1020;
//    SYSCTL_RCGCGPIO_R = 0x1020;

    // Enable pins 0-1 of GPIO-N and set to output
    GPION->DIR |= (D1 | D2);
    GPION->DEN |= (D1 | D2);

    // Enable pins 0 & 4 of GPIO-F and set to output
    GPIOF_AHB->DIR |= (D3 | D4);
    GPIOF_AHB->DEN |= (D3 | D4);

    while(1) {
        // Note that the version of the CMSIS file downloaded from
        // https://github.com/speters/CMSIS/tree/master/Device/TI/TM4C/Include
        // needed the GPIOA_AHB typedef modified to change "RESERVED0"
        // to "DATA_Bits" to conform to the CMSIS header used in the video
        GPION->DATA_Bits[D1 | D2] = D1;
        GPIOF_AHB->DATA_Bits[D3 | D4] = D3;

        delay(5e5);

        GPION->DATA_Bits[D1 | D2] = D2;
        GPIOF_AHB->DATA_Bits[D3 | D4] = D4;

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

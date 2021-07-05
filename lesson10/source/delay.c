#include "delay.h"

void delay(int iter) {
    volatile int counter = 0;
    while (counter < iter) {
        ++counter;
    }
}

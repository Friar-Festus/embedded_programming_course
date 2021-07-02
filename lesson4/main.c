

/**
 * main.c
 */

int main(void)
{
    // Turn on GPIO-F and -N blocks
    *((unsigned int *) 0x400FE608U) = 0x1020;

    // Enable pins 0-1 of GPIO-F and set to output
    *((unsigned int *) 0x40064400U) = 0x03;
    *((unsigned int *) 0x4006451CU) = 0x03;

    // Enable pins 0 & 4 of GPIO-N and set to output
        *((unsigned int *) 0x4005D400U) = 0x11;
        *((unsigned int *) 0x4005D51CU) = 0x11;

    while(1) {
        // Recall that bits 9:2 of address act as mask
        // for bits 7:0 of DATA. Yes, it's weird.
        *((unsigned int *) 0x4006400CU) = 0x02;
        *((unsigned int *) 0x4005D044U) = 0x10;

        int counter = 0;
        while (counter < 1000000) {
            ++counter;
        }

        *((unsigned int *) 0x4006400CU) = 0x01;
        *((unsigned int *) 0x4005D044U) = 0x01;

        counter = 0;
        while (counter < 1000000) {
            ++counter;
        }
    }

    //	return 0;
}

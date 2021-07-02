

/**
 * main.c
 */
int counter = 0;

int main(void)
{
    int *p_int;
    p_int = &counter;

    while (*p_int < 21) {
        ++*p_int;
        if ((*p_int & 1) != 0) {
            /* do something when the counter is odd */
        }
        else {
            /* do something when the counter is even */
        }
    }

        p_int = (int *) 0x20000000U;
        *p_int = 0xDEADBEEF;

	return 0;
}

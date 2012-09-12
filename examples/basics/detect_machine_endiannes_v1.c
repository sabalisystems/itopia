/**
 * @file: detect_machine_endiannes_v1.c
 * @compilation:
 *      gcc detect_machine_endiannes_v1.c -o detect_machine_endiannes_v1
 */

#include <stdio.h>

int
main(void)
{
        int n = 1;

        if (*(char *)&n == 1)
                printf("Little-endian\n");
        else if (*(((char *)&n) + 3) == 1)
                printf("Big-endian\n");
        else
                printf("Other-endian\n");

        return (0);
}


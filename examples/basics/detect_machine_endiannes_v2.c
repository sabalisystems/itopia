
/**
 * @file: detect_machine_endiannes_v2.c
 * @compilation:
 *      gcc detect_machine_endiannes_v2.c -o detect_machine_endiannes_v2
 */

#include <stdio.h> 

#if defined(__linux__)
 #include <endian.h>
 #define BYTE_ORDER __BYTE_ORDER
#elif defined(__FreeBSD__) || defined (__OpenBSD__) || defined(__NetBSD__)
 #include <machine/endian.h>
#elif defined(__APPLE__)
 #include <architecture/byte_order.h>
 #if __LITTLE_ENDIAN__
 # define BYTE_ORDER 1234         
 #elif __LITTLE_ENDIAN__
 # define BYTE_ORDER 4321     
 #endif
#endif

#ifndef LITTLE_ENDIAN
# define LITTLE_ENDIAN 1234
#endif

#ifndef BIG_ENDIAN
# define BIG_ENDIAN 4321
#endif

#ifndef BYTE_ORDER
# define BYTE_ORDER BIG_ENDIAN
#endif

int
main(void)
{

        if (BYTE_ORDER == LITTLE_ENDIAN)
                printf("Little-endian\n");
        else if (BYTE_ORDER == BIG_ENDIAN)
                printf("Big-endian\n");
        else
                printf("Other-endian\n");

        return (0);
}


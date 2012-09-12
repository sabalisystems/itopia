/**
 * @file: network_and_host_byte_order_examples.c
 * @compilation:
 *      gcc network_and_host_byte_order_examples.c -o example
 */

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

int
main(void)
{
        int16_t n_signed_16b, h_signed_16b;
        uint16_t n_unsigned_16b, h_unsigned_16b;

        h_signed_16b = -128;
        n_signed_16b = htons(h_signed_16b);
        h_unsigned_16b = 128;
        n_unsigned_16b = htons(h_unsigned_16b);

        printf("16bits (signed), value=%d\n", h_signed_16b);
        printf("-- host-byte-order: {0x%X, 0x%X}\n",
                *((char *)&h_signed_16b),
                *(((char *)&h_signed_16b) + 1) );
        printf("-- network-byte-order: {0x%X, 0x%X}\n",
                *((char *)&n_signed_16b),
                *(((char *)&n_signed_16b) + 1) );
        assert((int16_t)ntohs(n_signed_16b) == h_signed_16b);

        printf("16bits (unsigned), value=%d\n", h_unsigned_16b);
        printf("-- host-byte-order: {0x%X, 0x%X}\n",
                *((char *)&h_unsigned_16b),
                *(((char *)&h_unsigned_16b) + 1) );
        printf("-- network-byte-order: {0x%X, 0x%X}\n",
                *((char *)&n_unsigned_16b),
                *(((char *)&n_unsigned_16b) + 1) );
        assert((uint16_t)ntohs(n_unsigned_16b) == h_unsigned_16b);

        return (0);
}


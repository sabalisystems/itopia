/**
 * @file: custom_byte_order_conversion_functions.c
 * @compilation:
 *      gcc custom_byte_order_conversion_functions.c -o example
 */

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

static int16_t
simple1_short_conversion(int16_t value)
{
	int16_t retval = 0;
	uint8_t *ptr1, *ptr2;

	ptr1 = (uint8_t *)&value;
	ptr2 = (uint8_t *)&retval;
	
	// Zamnieniamy kolejnosc bajtow
	ptr2[0] = ptr1[1];
	ptr2[1] = ptr1[0];

	return retval;
}

static int16_t
simple2_short_conversion(int16_t value)
{

	return ( ((value & 0x00FF) << 8) | ((value & 0xff00) >> 8) );
}


#define	simple1_htons(v) simple1_short_conversion(v)
#define	simple1_ntohs(v) simple1_htons(v)

#define simple2_htons(v) simple2_short_conversion(v)
#define simple2_ntohs(v) simple2_htons(v)

#define	my_ntohs(v) ( ((v & 0x00FF) << 8) | ((v & 0xff00) >> 8) )
#define	my_htons(v) my_ntohs(v)

#define	my_ntohll(v) (((v & 0x00000000000000FF) << 56) |\
   ((v & 0x000000000000FF00) << 40) | 			\
   ((v & 0x0000000000FF0000) << 24) |			\
   ((v & 0x00000000FF000000) << 8)  |			\
   ((v & 0x000000FF00000000) >> 8)  |			\
   ((v & 0x0000FF0000000000) >> 24) |			\
   ((v & 0x00FF000000000000) >> 40) |			\
   ((v & 0xFF00000000000000) >> 56))

#define my_htonll(v) my_ntohll(v)

int
main(void)
{
        int16_t a = -128, b;
	int64_t c = -123456;
	
	assert(simple1_htons(a) == simple2_htons(a));
	assert(simple2_htons(a) == (int16_t)my_htons(a));
	assert((int16_t)my_htons(a) == (int16_t)htons(a));

	b = htons(a);
	
	assert(simple1_ntohs(b) == simple2_ntohs(b));
	assert(simple2_ntohs(b) == (int16_t)my_ntohs(b));
	assert((int16_t)my_ntohs(b) == (int16_t)ntohs(b));

	assert((int64_t)my_ntohll((int64_t)my_htonll(c)) == c);

        return (0);
}

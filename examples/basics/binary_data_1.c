/**
 * @file: binary_data_1.c
 * @compilation:
 *	gcc binary_data_1.c -o example
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static void
write_read_and_process_text_data(uint8_t number)
{
	FILE *fp = NULL;
	uint8_t tmpnum;
	char buff[16], *ptr, c;

	// Otworzenie pliku, zapisanie i zamkniecie pliku
	assert(snprintf(buff, sizeof(buff), "%d\n", (int)number) > 0); 
	assert((fp = fopen("data.txt", "w")) != NULL);
	assert(fwrite(buff, 1, strlen(buff), fp) > 0);
	fclose(fp);

	// Otworzenie pliku, odczytanie (pierwszej lini) i zamkniecie pliku
	assert((fp = fopen("data.txt", "r")) != NULL);
	memset(buff, 0, sizeof(buff));
	ptr = buff;
	while( (c = getc(fp)) != '\n' )
		*(ptr++) = c;
	*ptr = '\0';
	tmpnum = (uint8_t)atoi(buff);
        fclose(fp);

	// Wyswietlenie na ekranie - kwadrat odczytanej liczby
	printf("text-way: %d\n", (int)(tmpnum * tmpnum));
}

static void
write_read_and_process_binary_data(uint8_t number)
{
	FILE *fp = NULL;
        uint8_t tmpnum;

	// Otworzenie pliku, zapisanie i zamkniecie pliku
	assert((fp = fopen("data.bin", "wb")) != NULL);
        assert(fwrite(&number, 1, sizeof(uint8_t), fp) > 0);
	fclose(fp);	

	// Otworzenie pliku, odczytanie i zamkniecie pliku
        assert((fp = fopen("data.bin", "rb")) != NULL);
	assert(fread(&tmpnum, 1, sizeof(uint8_t), fp) > 0);
	fclose(fp);

	// Wyswietlenie na ekranie - kwadrat odczytanej liczby
        printf("binary-way: %d\n", (int)(tmpnum * tmpnum));	
}

int
main(void)
{
	uint8_t number = 201;

	write_read_and_process_text_data(number);	
	write_read_and_process_binary_data(number);	

	return (0);
}


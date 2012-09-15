/**
 * @file: binary_data_2.c
 * @compilation:
 *      gcc binary_data_2.c -o example
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define	BINPACK_MAXSIZE		(1024)

struct binpack {
	unsigned char raw_data[BINPACK_MAXSIZE];
	unsigned char *ptr;
	uint32_t size;
	uint32_t maxsize;
};

static int
binpack_reset(struct binpack *binpackp)
{
	
	if (!binpackp)
		return (1);

	memset(binpackp->raw_data, 0, BINPACK_MAXSIZE);
	binpackp->ptr = binpackp->raw_data;
	binpackp->size = 0;
	binpackp->maxsize = BINPACK_MAXSIZE;
	
	return (0);
}

static const unsigned char *
binpack_dataptr(struct binpack *binpackp)
{

	assert(binpackp != NULL);
	return binpackp->raw_data;
}

static size_t
binpack_datalen(struct binpack *binpackp)
{
	assert(binpackp != NULL);
	return binpackp->size;
}

static unsigned char *
binpack_push(const void *data, size_t datalen,
			 struct binpack *binpackp)
{

	if ((binpackp->size + datalen) > binpackp->maxsize)
		return (NULL);
	
	memcpy(binpackp->ptr, data, datalen);
	binpackp->ptr += datalen;
	binpackp->size += datalen;
	
	return binpackp->ptr;
}

/// ---

struct userdata {
	char name[8];
	int age;
};

static void
print_userdata(const unsigned char *data)
{
	struct userdata *ud;

	assert(data != NULL);
	ud = (struct userdata *)data;
	printf("user name=%s, age=%d\n", ud->name, ud->age);	
} 

static void
print_integer(const char *name, const unsigned char *data)
{
	assert(data != NULL && name != NULL);
	printf("%s = %d\n", name, *((int *)data));	
}

static void
print_all_data(const unsigned char *data)
{
	const unsigned char *ptr;
	
	assert((ptr = data) != NULL);
	
	// Odczyt/interpretacja danych binarnych
	print_integer("a", ptr);
	ptr += sizeof(int);

	print_integer("b", ptr);          
        ptr += sizeof(int);
		
	print_userdata(ptr);
	ptr += sizeof(struct userdata);

	print_userdata(ptr);
        ptr += sizeof(struct userdata);
}

int
main(void)
{
	FILE *fp = NULL;
	struct binpack bp;
	unsigned char buff[1024], tmp[1024], *ptr;
	int a = 1, b = 2;
	struct userdata users[2] = {{"janek", (21)}, {"franek", (12)}};

	/// Pakowanie, wersja "na piechote"
	/* Ustawiamy wskaznik na poczatek bufora */
	ptr = buff;
	/* Kopiujemy 4-bajtowa liczbe do bufora */
	memcpy(ptr, &a, sizeof(int));
	/* Przesuwamy wskaznik o 4 bajty, czyli na koniec danych */
	ptr += sizeof(int);
	/* Kopiujemy znowu 4-bajtowa liczbe do bufora */ 
	memcpy(ptr, &b, sizeof(int));
	/* Przesuwamy wskaznik o kolejne 4 bajty */
	ptr += sizeof(int);
	/* Kopiujemy struktury - koniec */
	memcpy(ptr, users, sizeof(users)); 	

	// Pakowanie, wersja "ulepszona"
	binpack_reset(&bp);
	binpack_push(&a, sizeof(int), &bp);
	binpack_push(&b, sizeof(int), &bp);
	binpack_push(users, sizeof(users), &bp);

	assert(memcmp(buff, binpack_dataptr(&bp),
				  binpack_datalen(&bp)) == 0);

	// Otworzenie pliku, zapisanie danych binarnych i zamkniecie pliku
	assert((fp = fopen("data.bin", "wb")) != NULL);
	assert(fwrite(buff, 1, binpack_datalen(&bp), fp) > 0);
	fclose(fp);

	// Otworzenie pliku, odczytanie danych binarnych i zamkniecie pliku
	assert((fp = fopen("data.bin", "rb")) != NULL);
	assert(fread(tmp, 1, binpack_datalen(&bp), fp) > 0);
	fclose(fp);

	// Wyswietlenie wynikow
	printf("Rozmiar ciagu danych binarnych: %d bajt(y/ow)\n", 
		   (int)binpack_datalen(&bp));
	printf("\nDane - wersja \"na piechote\":\n");
	print_all_data(buff);
	printf("\nDane - wersja \"ulepszona\":\n");
	print_all_data(binpack_dataptr(&bp));		
	printf("\nDane odczytane z pliku\n");
	print_all_data(tmp);

	return (0);
}


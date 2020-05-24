#include <errno.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include "tcs34725.h"


int main (void)
{
	int fd;
	uint8_t red, grn, blu; 		/* normalleştirilmiş RGB değerleri*/

	fd = tcs34725_init();
	if (fd == -1)
	{
		fprintf(stderr, "Baslangic hatasi!\n");
		return (-1);
	}


	/* renk okuma */
	for (;;)
	{
		nanosleep(&integration_time, NULL);
		tcs34725_get_color(fd, &red, &grn, &blu);
		printf("Renk: #%02X%02X%02X\n", red, grn, blu);
	}
	return(0);
}

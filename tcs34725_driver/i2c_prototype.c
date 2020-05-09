#include <errno.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <time.h>
#include "tcs34725.h"


int main (void)
{
	int fd;
	uint8_t id, r, g, b, c;
	struct timespec integration_time; /* Gerekli bekleme süresi */
	integration_time.tv_sec = 0;
	integration_time.tv_nsec = INT_TIME /* 101 ms */
	fd = wiringPiI2CSetup (SLAVE_ID);
	if (fd == -1)
	{
		printf ("wiringPiI2CSetup hata, errno: %d\n", errno);
		return (-1);
	}
	id = wiringPiI2CReadReg8 (fd, REG_ID); /* baglanti kontrolu */
	if (id != ID_VAL)
	{
		printf ("I2C baglanti hatasi!\n Okunan ID: %x\n", id);
		return (-1);
	}
	/* baslangic rutini */
	wiringPiI2CWriteReg8 (fd, REG_ATIME, ATIME_VAL);
	wiringPiI2CWriteReg8 (fd, REG_EN, (AEN_MASK | PON_MASK));

	/* renk okuma */
	for(;;)
	{
		nanosleep(&integration_time, NULL);
		c = (uint8_t) (wiringPiI2CReadReg8 (fd, REG_CDATAH));
		r = (uint8_t) (wiringPiI2CReadReg8 (fd, REG_RDATAH));
		g = (uint8_t) (wiringPiI2CReadReg8 (fd, REG_GDATAH));
		b = (uint8_t) (wiringPiI2CReadReg8 (fd, REG_BDATAH));
		printf	("Clear: %x 	RGB:#%x%x%x", c, r, g, b);
	}
	return (0)

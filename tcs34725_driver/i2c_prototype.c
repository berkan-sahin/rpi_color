#include <errno.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include "tcs34725.h"


int main (void)
{
	int fd;
	uint8_t id, red, grn, blu; 		/* normalleştirilmiş RGB değerleri*/ 
	uint16_t r_raw, g_raw, b_raw, c_raw; 	/* sensörden gelen saf değerler */
	uint32_t toplam; 			/* normalleştirme algoritması için gerekli */

	struct timespec integration_time; 	/* Gerekli bekleme süresi */
	integration_time.tv_sec = 0;
	integration_time.tv_nsec = INT_TIME; 	/* 101 ms */

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
		c_raw = (uint16_t) (wiringPiI2CReadReg16 (fd, REG_CDATAL));
		r_raw = (uint16_t) (wiringPiI2CReadReg16 (fd, REG_RDATAL));
		g_raw = (uint16_t) (wiringPiI2CReadReg16 (fd, REG_GDATAL));
		b_raw = (uint16_t) (wiringPiI2CReadReg16 (fd, REG_BDATAL));
		
		/* Normalleştirme algoritması */
		toplam = c_raw;
		if (toplam == 0)
			red = grn = blu = 0;	/* Eğer clear 0 ise siyah renk döndür */
		
		red = (uint8_t) ((float)r_raw / toplam * 255.0);
		grn = (uint8_t) ((float)g_raw / toplam * 255.0);
		blu = (uint8_t) ((float)b_raw / toplam * 255.0);

		printf ("Renk: #%02X%02X%02X\n", red, grn, blu);
	}
	return (0);
}

#include "tcs34725.h"

int tcs34725_init()
{
    int fd = wiringPiI2CSetup(SLAVE_ID);
    if ( fd == -1 )
    {
        perror("I2C Kurulum hata");
        return(-1);
    }

    uint8_t id = wiringPiI2CReadReg8(fd, REG_ID);
    if ( id != ID_VAL )
    {
        fprintf(stderr, "ID dogru degil!\n");
        return(-1);
    }

    if ( wiringPiI2CWriteReg8(fd, REG_ATIME, ATIME_VAL) < 0 )
    {
        perror("tcs34725_init");
        return(-1);
    }

    if ( wiringPiI2CWriteReg8(fd, REG_EN, (AEN_MASK | PON_MASK) ) < 0)
    {
        perror("tcs34725_init");
        return(-1);
    }

    return(fd);

}

void tcs34725_get_color(int fd, uint8_t *r, uint8_t *g, uint8_t *b)
{
    uint16_t c_raw, r_raw, g_raw, b_raw;
    uint32_t toplam;
    c_raw = (uint16_t) (wiringPiI2CReadReg16(fd, REG_CDATAL));
    r_raw = (uint16_t) (wiringPiI2CReadReg16(fd, REG_RDATAL));
    g_raw = (uint16_t) (wiringPiI2CReadReg16(fd, REG_GDATAL));
    b_raw = (uint16_t) (wiringPiI2CReadReg16(fd, REG_BDATAL));

    /* Normalleştirme algoritması */
    toplam = c_raw;
    if (toplam == 0)
        *r = *g = *b = 0;    /* Eğer clear 0 ise siyah renk döndür */

    *r = (uint8_t) ((float)r_raw / toplam * 255.0);
    *g = (uint8_t) ((float)g_raw / toplam * 255.0);
    *b = (uint8_t) ((float)b_raw / toplam * 255.0);
}

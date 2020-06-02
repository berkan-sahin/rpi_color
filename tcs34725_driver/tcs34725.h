#ifndef TCS34725
#define TCS34725

#include <stdint.h>
#include <time.h>
#include <wiringPiI2C.h>
#include <errno.h>
#include <stdio.h>

#define SLAVE_ID 	0x29
#define REG_EN   	0x80
#define REG_ATIME	0x81
#define REG_ID		0x92
#define REG_STATUS	0x93
#define REG_CDATAL	0x94
#define REG_CDATAH	0x95
#define REG_RDATAL	0x96
#define REG_RDATAH	0x97
#define REG_GDATAL	0x98
#define REG_GDATAH	0x99
#define REG_BDATAL	0x9A
#define REG_BDATAH	0x9B
#define AEN_MASK	0x02
#define PON_MASK	0x01
#define ATIME_VAL	0xC0
#define ID_VAL		0x44


#define NS_TO_MS	100000

int tcs34725_init();
void tcs34725_get_color(int fd, uint8_t *r, uint8_t *g, uint8_t *b);

#ifdef MAIN
struct timespec integration_time = { .tv_sec = 0 , .tv_nsec = 101 * NS_TO_MS};
#endif
//integration_time.tv_sec = 0;
//integration_time.tv_nsec = 101 * NS_TO_MS;

#endif //tcs34725.h

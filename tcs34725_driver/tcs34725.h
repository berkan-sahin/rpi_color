#ifndef TCS34725
#define TCS34725



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
const long INT_TIME = 101 * NS_TO_MS;

#endif //tcs34725.h

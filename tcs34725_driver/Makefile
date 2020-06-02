##
# TCS34725 Driver
#
# @file
# @version 0.1
color_server : tcs34725.o color_server.c
	gcc -o color_server tcs34725.o color_server.c -lwiringPi -lrt

tcs34725.o : tcs34725.c tcs34725.h
	gcc -c tcs34725.c

i2c_test : tcs34725.o i2c_prototype.c
	gcc -o i2c_test tcs34725.o i2c_prototype.c -lwiringPi

clean :
	rm tcs34725.o i2c_test
# end

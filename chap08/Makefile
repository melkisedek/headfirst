CFLAGS=-Wall -g

test_code:
	gcc -c checksum.c -o checksum.o
	gcc -c encrypt.c -o encrypt.o
	gcc test_code.c encrypt.o checksum.o -o test_code

clean:
	rm test_code elliptical

clean_all:
	rm *.o test_code

elliptical:
	gcc -I./includes -c hfcal.c -o libs/hfcal.o
	ar -rcs libs/libhfcal.a libs/hfcal.o
	gcc elliptical.c -o elliptical.o -I./includes -L./libs -lhfcal -o elliptical 

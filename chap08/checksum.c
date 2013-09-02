#include "checksum.h"

int checksum(char *message){
	int c = 0;
	while(*message){
	//cast to integer and perform binary xor
	c += c ^ (int)(*message);
	message++;
	}
	return c;
}

#include <stdio.h>

typedef union{
	float weight;
	int count;
} cupcake;

int main(){
	/*By mistake the programmer has set the weight NOT the count*/
	cupcake order = {2};
	/*He set the weight, but he's reading the count*/
	printf("Cupcakes quantity: %i\n", order.count);
	return 0;
}

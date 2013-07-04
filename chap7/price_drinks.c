#include <stdio.h>
#include <stdarg.h>

enum drink {
	MUDSLIDE, FUZZY_NAVEL, MONKEY_GLAND, ZOMBIE
};

double price(enum drink d){
	switch(d){
	case MUDSLIDE:
		return 6.79;
	case FUZZY_NAVEL:
		return 5.31;
	case MONKEY_GLAND:
		return 4.82;
	case ZOMBIE:
		return 5.89;
	}
	return 0;
}

void print_ints(int args, ...){
        va_list ap;
        va_start(ap, args);

        int i;
        for(i = 0; i < args; i++){
                printf("argument: %i\n", va_arg(ap, int));
        }
        va_end(ap);
}

double total(int args, ...){
	double total = 0;
	va_list ap;
	va_start(ap, args);

	int i;
	for(i = 0; i < args; i++){
		enum drink d = va_arg(ap, enum drink);
		total +=price(d);
	}
	va_end(ap);
	return total;
}

int main(){
	printf("Price is %.2f\n", total(2, MONKEY_GLAND, MUDSLIDE));
	printf("Price is %.2f\n", total(3, MONKEY_GLAND, MUDSLIDE, FUZZY_NAVEL));
	printf("Price is %.2f\n", total(1, ZOMBIE));
//        print_ints(3, 79, 101, 32);
        return 0;
}


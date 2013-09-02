#include <stdio.h>
/*Never do this in C!*/

int main(){
/*This("JQK") is put into CONSTANTS(read-only memory)
*And therefore can't be updated by using(*cards),that code will segfault.
*But cards[] will work because it creates a stack copy from the constant.
*/
	char cards[] = "JQK";
	char a_card = cards[2];
	cards[2] = cards[1];
	cards[1] = cards[0];
	cards[0] = cards[2];
	cards[2] = cards[1];
	cards[1] = a_card;
	puts(cards);
	return 0;
}

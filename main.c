#include <stdio.h>
#define DL_BIGINT
#include "cl_bigint.h"



void print(bigint *N) {
	if(N == NULL) {
		printf("NaN");
	} else {
		bigint *tmp = N;

		do {
			printf("%d",tmp->x);
			tmp = tmp->next;
		} while(tmp != N);
	}
}

int main() {

    bigint* n1 = str2bigint_rec("1234");
	n1->x *= -1;
	printf("\n");
    bigint* n2 = str2bigint_rec("76763");
	n2->x *= -1;

	bigint* n3 = mul(n1,n2);
    int x = (-2) % 10;
    //printf("%d\n", x);
	print(n1); printf("*"); print(n2); printf(" == "); print(n3);
    return 0;
}

#include <stdio.h>
#define DL_BIGINT
#include "dl_bigint.h"


void print(bigint *N) {
	if(N == NULL) {
		printf("NaN");
	} else {
		bigint *tmp = N;

		do {
			printf("%d",tmp->x);
			tmp = tmp->next;
		} while(tmp != NULL);
	}
}

int main() {
    int n1int[] = {3, 2, 1};
    int n2int[] = {3, 2, 1};
    bigint* n1 = str2bigint_rec("4367376");
	print(n1);
	printf("\n");
    bigint* n2 = str2bigint_rec("76763");
	print(n2);
    bigint* n3 = mul(n1,n2);
    int x = (-2) % 10;
    printf("%d\n", x);
	print(n3);
    return 0;
}

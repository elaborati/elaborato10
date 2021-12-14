#define DL_BIGINT /* TODO: DA RIMUOVERE AL MOMENTO DELLA CONSEGNA */
#ifdef DL_BIGINT
#include <stdlib.h>
#include "dl_bigint.h"
#include <stdlib.h>

static bigint* bigint_alloc(digit x) {
    bigint* tmp = (bigint*)malloc(sizeof(bigint));

    if (tmp != NULL) {
        tmp->x = x;
        tmp->next = NULL;
        tmp->prev = NULL;
    }
    return tmp;
}

static int head_insert(bigint** N, digit x) {
    if (N == NULL) {
        return 1;
    }
    else if (*N == NULL) {
        return (*N = bigint_alloc(x)) == NULL;
    }
    else {
        bigint* tmp = bigint_alloc(x);

        if (tmp != NULL) {
            tmp->next = *N;
            (*N)->prev = tmp;
            *N = tmp;
        }
        return tmp == NULL;
    }
}
bigint *str2bigint_rec(char *s) {
	bigint *N = NULL;

	if(*s != '\0') {
		N = str2bigint_rec(s+1);
		head_insert(&N,(*s) - '0');
	}
	return N;
}


static bigint* getTail(bigint* N) {
    bigint* node = N;
    while (node->next != NULL) {
        node = node->next;
    }
    return node;
}

static int utilityForCarry(bigint** n, digit x) {
	if((*n)->prev == NULL) {
		return head_insert(n, x);
	}
	(*n) = (*n)->prev;
	(*n)->x += x;
	return 1;
}



bigint *mul(bigint *N1, bigint *N2) {
    bigint* res = bigint_alloc(0);
    bigint* tail1 = getTail(N1);
    bigint* tail2 = getTail(N2);
    bigint* tailRes = getTail(res);

	for(N1 = tail1; N1 != NULL; N1 = N1->prev, tailRes = tailRes->prev) {
		for(N2 = tail2, res = tailRes; N2 != NULL; N2 = N2->prev) {
            digit product = (N1->x) * (N2->x);
            digit actualDigit = product % 10;
            if(res == NULL)
                head_insert(&res, product);
            else {
                (res->x) += product;
            }
			digit carry = res->x / 10;
            res->x %= 10;
			utilityForCarry(&res, carry);
        }

    }
    return res;
}



#endif
//#define DL_BIGINT /* TODO: DA RIMUOVERE AL MOMENTO DELLA CONSEGNA */
#ifdef DL_BIGINT
#include <stdlib.h>
#include "dl_bigint.h"
#include <stdlib.h>

static void absInPlace(bigint* n);
static digit computeSign(bigint* n1, bigint* n2);


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

static int bigint_delete(bigint* N) {
	if (N == NULL) {
		return 1;
	}
	else {
		if (N->next != NULL)
			N->next->prev = N->prev;
		if (N->prev != NULL)
			N->prev->next = N->next;
		free(N);
		return 0;
	}
}

static int head_delete(bigint** N) {
	if (N == NULL || *N == NULL) {
		return 1;
	}
	else {
		bigint* tmp = *N;

		*N = (*N)->next;
		return bigint_delete(tmp);
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

static void absInPlace(bigint* n) {
	if(n->x < 0)
		n->x *= -1;
}

static digit computeSign(bigint* n1, bigint* n2) {
	if(n1->x * n2->x < 0)
		return -1;
	else
		return 1;
}

static void remove_leading_zeros(bigint** N) {
	if (N != NULL) {
		while (*N != NULL && (*N)->x == 0 && (*N)->next != NULL)
			head_delete(N);
	}
}

static int wellFormedBigint(bigint* n) {
	if (n->x > 9 || n->x < -9)
		return 0;
	n = n->next;
	for(; n != NULL; n = n->next)
		if(n->x > 9 || n->x < 0)
			return 0;
	return 1;
}

bigint *mul(bigint *N1, bigint *N2) {
	if(N1 == NULL || N2 == NULL)
		return NULL;
	if(!wellFormedBigint(N1) || !wellFormedBigint(N2))
		return NULL;

    bigint* res = bigint_alloc(0);
    bigint* tail1 = getTail(N1);
    bigint* tail2 = getTail(N2);
    bigint* tailRes = getTail(res);
	digit sign = computeSign(N1, N2);
	absInPlace(N1);
	absInPlace(N2);


	N1 = tail1;
	do {

		N2 = tail2;
		res = tailRes;
		do {
			digit product = (N1->x) * (N2->x);
			(res->x) += product;
			digit carry = res->x / 10;
			res->x %= 10;
			utilityForCarry(&res, carry);

			N2 = N2->prev;
		} while(N2 != NULL);

		N1 = N1->prev;
		tailRes = tailRes->prev;
	} while(N1 != NULL);

	remove_leading_zeros(&res);
	res->x *= sign;
    return res;
}



#endif
#define CL_BIGINT /* TODO: DA RIMUOVERE AL MOMENTO DELLA CONSEGNA */
#ifdef CL_BIGINT
#include <stdlib.h>
#include "dl_bigint.h"
#include <stdlib.h>

static void absInPlace(bigint* n);
static digit computeSign(bigint* n1, bigint* n2);


#define C2N(c) ((c)-'0')

static bigint *bigint_alloc(digit x) {
	bigint *tmp = (bigint *)malloc(sizeof(bigint));

	if(tmp != NULL) {
		tmp->x    = x;
		tmp->next = tmp;
		tmp->prev = tmp;
	}
	return tmp;
}

static int bigint_delete(bigint *N) {
	if(N == NULL) {
		return 1;
	} else {
		bigint *prv = N->prev, *nxt = N->next;
		nxt->prev = prv;
		prv->next = nxt;
		free(N);
		return 0;
	}
}

static int bigint_insert(bigint *N, digit x) {
	if(N == NULL) {
		return 1;
	} else {
		bigint *tmp = bigint_alloc(x), *nxt = N->next, *prv = N;
		if(tmp != NULL) {
			tmp->prev = prv;
			tmp->next = nxt;
			prv->next = tmp;
			nxt->prev = tmp;
		}
		return tmp == NULL;
	}
}

static int head_insert(bigint **N, digit x) {
	if(N == NULL)
		return 1;
	else if(*N == NULL)
		return (*N = bigint_alloc(x)) == NULL;
	else if (bigint_insert((*N)->prev,x) == 1)
		return 1;
	else
		return (*N = (*N)->prev) == NULL;
}

static int head_delete(bigint **N) {
	if(N == NULL || *N == NULL) {
		return 1;
	} else if (*N == (*N)->next) {
		free(*N);
		*N = NULL;
		return 0;
	} else {
		*N = (*N)->next;
		return bigint_delete((*N)->prev);
	}
}

static void remove_leading_zeros(bigint **N) {
	if(N != NULL && *N != NULL) {
		while((*N)->x == 0 && *N != (*N)->next)
			head_delete(N);
	}
}


bigint *str2bigint_rec(char *s) {
	bigint *N = NULL;

	if(*s != '\0') {
		N = str2bigint_rec(s+1);
		head_insert(&N,C2N(*s));
	}
	return N;
}

static bigint* getTail(bigint* N) {
    return N->prev;
}

static bigint* getHead(bigint* N) {
	return N;
}


static int moveHead(bigint** n, digit x, bigint* tail) {
	if((*n)->prev == tail) {
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

static int wellFormedBigint(bigint* n) {
	if (n->x > 9 || n->x < -9)
		return 0;
	bigint* _n = n->next;

	for(; _n != n; _n = _n->next)
		if(_n->x > 9 || _n->x < 0)
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
	bigint* _tailRes = getTail(res);
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
			moveHead(&res, carry, _tailRes);

			N2 = N2->prev;
		} while(N2 != tail2);

		N1 = N1->prev;
		tailRes = tailRes->prev;
	} while(N1 != tail1);

	remove_leading_zeros(&res);
	res->x *= sign;
    return res;
}



#endif

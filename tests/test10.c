#include <stdio.h>
#include <stdlib.h>

#include "napiernaf.h"

void pokaz(int *a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%+d", a[i]);
    }
    printf("; (%d)\n", ntoi(a, n));
}

int main(void) {
    int *a, an;
    iton(10, &a, &an);
    pokaz(a, an);
    int *b, bn;
    b = NULL;
    for (int i = 0; i < 5; ++i) {
        int *x;
        bn = an;
        nmul(a, an, a, an, &x, &an);
        free(b);
        b = a;
        a = x;
        pokaz(a, an);
    }
    int *c, cn, *d, dn;
    int *e, en;
    iton(7, &e, &en);
    int *f, fn;
    nmul(b, bn, e, en, &f, &fn);
    ndivmod(a, an, f, fn, &c, &cn, &d, &dn);
    pokaz(c, cn);
    pokaz(d, dn);
    pokaz(e, en);
    pokaz(f, fn);
    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    free(f);
    return 0;
}

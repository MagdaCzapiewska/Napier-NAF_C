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
    iton(10000, &a, &an);
    int *b, bn;
    iton(-10001, &b, &bn);
    int *c, cn;
    nadd(a, an, b, bn, &c, &cn);
    int *d, dn;
    nsub(a, an, b, bn, &d, &dn);
    int *e, en;
    nmul(c, cn, d, dn, &e, &en);
    pokaz(a, an);
    pokaz(b, bn);
    pokaz(c, cn);
    pokaz(d, dn);
    pokaz(e, en);
    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    return 0;
}

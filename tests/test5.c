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
    iton(1024, &a, &an);
    int *b, bn;
    iton(-1023, &b, &bn);
    int *c, cn;
    nadd(a, an, b, bn, &c, &cn);
    int *d, dn;
    nsub(a, an, b, bn, &d, &dn);
    int *e, en;
    nmul(c, cn, d, dn, &e, &en);
    int *f, fn;
    nexp(a, an, d, dn, &f, &fn);
    pokaz(a, an);
    pokaz(b, bn);
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

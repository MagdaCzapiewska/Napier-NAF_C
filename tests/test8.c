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
    iton(-12, &a, &an);
    pokaz(a, an);
    for (int i = 0; i < 7; ++i) {
        int *b = a;
        nmul(a, an, a, an, &a, &an);
        free(b);
    }
    int *c, cn;
    iton(-10, &c, &cn);
    int *d, dn, *e, en;
    ndivmod(a, an, c, cn, &d, &dn, &e, &en);
    pokaz(a, an);
    pokaz(c, cn);
    pokaz(d, dn);
    pokaz(e, en);
    free(a);
    free(c);
    free(d);
    free(e);
    return 0;
}

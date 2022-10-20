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
    int a[] = {-1, -77, 100, 102, -77232917};
    int an = sizeof a / sizeof *a;
    int b[] = {-1, -3, -5, 100, 200, 74207281};
    int bn = sizeof b / sizeof *b;
    int *c, cn;
    iton(12345, &c, &cn);
    int *d, dn;
    nadd(a, an, b, bn, &d, &dn);
    int *e, en;
    nsub(a, an, c, cn, &e, &en);
    int *f, fn;
    nmul(b, bn, c, cn, &f, &fn);
    int *g, gn, *h, hn;
    ndivmod(f, fn, c, cn, &g, &gn, &h, &hn);
    pokaz(a, an);
    pokaz(b, bn);
    pokaz(c, cn);
    pokaz(d, dn);
    pokaz(e, en);
    pokaz(f, fn);
    pokaz(g, gn);
    pokaz(h, hn);
    free(c);
    free(d);
    free(e);
    free(f);
    free(g);
    free(h);
    return 0;
}

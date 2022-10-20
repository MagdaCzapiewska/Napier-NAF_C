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
    int a[] = {-1, -10, -77, -100, 150, 152, 154, -157, -1000, 2000, -77232917};
    int an = sizeof a / sizeof *a;
    int b[] = {-1, -3, -5, -7, -9, 100, 102, 104, 10000};
    int bn = sizeof b / sizeof *b;
    int *c, cn;
    iton(1025, &c, &cn);
    int *d, dn;
    nadd(a, an, b, bn, &d, &dn);
    int *e, en;
    nsub(a, an, c, cn, &e, &en);
    int *f, fn;
    nmul(b, bn, c, cn, &f, &fn);
    int *g, gn;
    iton(15, &g, &gn);
    int *h, hn;
    nexp(b, bn, g, gn, &h, &hn);
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

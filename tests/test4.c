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
    iton(16, &a, &an);
    int *j, jn;
    iton(1, &j, &jn);
    pokaz(a, an);
    for (int i = 0; i < 7; ++i) {
        int *b = a;
        int *c, cn;
        nmul(a, an, a, an, &c, &cn);
        nsub(c, cn, j, jn, &a, &an);
        free(b);
        free(c);
    }
    pokaz(a, an);
    free(a);
    free(j);
    return 0;
}

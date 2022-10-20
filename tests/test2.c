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
    iton(-3, &a, &an);
    pokaz(a, an);
    for (int i = 0; i < 6; ++i) {
        int *b = a;
        nmul(a, an, a, an, &a, &an);
        free(b);
    }
    pokaz(a, an);
    free(a);
    return 0;
}

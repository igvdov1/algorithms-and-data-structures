#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main() {
    int cnt;
    long long n, weight, curr_w, c, fmask = 0, Cnt = 0, C1 = 0;

    scanf("%llu %llu", &n, &weight);
    long long *W = (long long *) malloc(n * sizeof(long long));
    long long *C = (long long *) malloc(n * sizeof(long long));
    for (int j = 0; j < n; ++j) {
        scanf("%llu %llu", &W[j], &C[j]);
    }
    for (long long mask = 1; mask < (1u << n); ++mask) {
        curr_w = 0;
        c = 0;
        cnt = 0;
        for (int i = 0; i < n; ++i)
            if ((mask >> i) & 1) {
                if (curr_w + W[i] <= weight) {
                    curr_w += W[i];
                    c += C[i];
                    cnt++;
                }
            }
        if (c > C1) {
            C1 = c;
            Cnt = cnt;
            fmask = mask;
        }
    }

    printf("%llu %llu\n", C1, Cnt);
    for (int i = 0; i < n; ++i)
        if ((fmask >> i) & 1) {
            printf("%d ", i + 1);
        }

    return 0;
}
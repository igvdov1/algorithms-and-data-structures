#include <stdio.h>
#include <malloc.h>

int proverka(int a[], int n, int k) {
    int **b;
    b = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        b[i] = (int *) malloc(k * sizeof(int *));
        for (int j = 0; j < k; ++j) {
            b[i][j] = -1;
        }
    }


    b[0][a[0]] = a[0];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < k; ++j) {
            if (b[i][j] != -1) {
                if ((j + a[i + 1]) % k >= 0) {
                    b[i + 1][(j + a[i + 1]) % k] = (j + a[i + 1]) % k;
                } else {
                    b[i + 1][(j + a[i + 1]) % k + k] = (j + a[i + 1]) % k + k;
                }
                if ((j - a[i + 1]) % k >= 0) {
                    b[i + 1][(j - a[i + 1]) % k] = (j - a[i + 1]) % k;
                } else {
                    b[i + 1][(j - a[i + 1]) % k + k] = (j - a[i + 1]) % k + k;
                }
            }
        }
    }

    if (b[n - 1][0] == 0) {
        return 1;
    }
    return 0;
}

int main() {
    int *a;
    int n;
    int k;
    int y;
    scanf("%d %d", &n, &k);
    a = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &y);
        if (y % k >= 0) {
            a[i] = y % k;
        } else {
            a[i] = y % k + k;
        }
    }

    if (proverka(a, n, k) == 1) {
        printf("Divisible");
    } else {
        printf("Not divisible");
    }
}
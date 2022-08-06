#include <stdio.h>
#include <malloc.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);
    long int y = pow(10, 9) + 7;
    long int **a = (long int **) malloc((n + 1) * sizeof(long int *));
    for (int i = 0; i <= n; i++) {
        a[i] = (long int *) malloc((n + 1) * sizeof(long int));
        for (int j = 0; j <= n; j++) {
            a[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        a[i][i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k < i; k++) {
            for (int j = 1; j <= k; j++) {
                a[i][k] = (a[i][k] + a[i - k][j]) % y;
            }
        }
    }
    long int sum = 0;
    for (int k = 1; k <= n; ++k) {
        sum = (sum + a[n][k]) % y;
    }
    printf("%ld\n", sum % y);
//    for(int i = 0; i <= n; i++){
//        for(int j = 0; j <= n; j++){
//            printf("%d", a[i][j]);
//        }
//        printf("\n");
//    }

}
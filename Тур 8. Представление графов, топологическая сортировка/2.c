#include <stdio.h>
#include <malloc.h>


int main() {
    int n, m, dop1, dop2;
    scanf("%d %d", &n, &m);
    int **a = (int *) malloc(sizeof(int *) * (n + 1));
    int *zeroes = (int *) calloc(sizeof(int), (n + 1));
    int *b = (int *) calloc(sizeof(int), (n + 1));
    for (int i = 1; i <= n; i++) {
        a[i] = (int *) calloc(sizeof(int), (n + 1));
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &dop1, &dop2);
        if (a[dop1][dop2] == 0) {
            zeroes[dop2]++;
        }
        a[dop1][dop2] = 1;
    }
    int count = 1, flag;
    while (count <= n + 1) {
        flag = 0;
        for (int i = 1; i <= n; i++) {
            if (zeroes[i] == 0) {
                zeroes[i] = -1;
                flag = 1;
                b[count++] = i;
                for (int j = 1; j <= n; j++) {
                    if (a[i][j] == 1) {
                        zeroes[j]--;
                        a[i][j] = 0;
                    }
                }
                break;
            }
        }
        if (flag == 0) {
            break;
        }
    }


    if (count - 1 == n) {
        for (int i = 1; i < count; i++) {
            printf("%d ", b[i]);
        }
    } else {
        printf("bad course");
    }


}
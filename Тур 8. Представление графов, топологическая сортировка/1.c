#include <stdio.h>
#include <malloc.h>
#include <math.h>

typedef struct ans {
    int sost;
    int pos;
} ans;

int FindZero(int **a, ans *b, int n) {
    for (int j = 0; j < n; j++) {
        int flag = 0;
        if (b[j].pos == 0) {
            for (int i = 0; i < n; i++) {
                if (a[i][j] == 1) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                return j;
            }
        }
    }
    return -1;
}

int main() {
    int n, k, dop1, dop2;
    ans *b;
    scanf("%d %d", &n, &k);
    b = (ans *) calloc(n, sizeof(ans));
    int **a = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {

        a[i] = (int *) calloc(n, sizeof(int));

    }
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &dop1, &dop2);
        a[dop1 - 1][dop2 - 1] = 1;
    }
    for (int i = 0; i < n; i++) {
        k = FindZero(a, b, n);
        if (k != -1) {
            b[k].pos = 1;
            b[i].sost = k + 1;
            for (int i = 0; i < n; i++) {
                a[k][i] = 0;
            }
        } else {
            printf("bad course");
            return 0;
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", b[i].sost);
    }

}


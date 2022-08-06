#include <stdio.h>
#include <malloc.h>

typedef struct in {
    int ves;
    int scet;
} in;

int max(int a_1, int a_2) {
    if (a_1 > a_2) {
        return a_1;
    } else {
        return a_2;
    }
}

int main() {
    int **a, n, k, s, v;
    in *b;
    scanf("%d %d", &n, &k);
    a = (int **) malloc(n * sizeof(int *));
    b = (in *) malloc(n * sizeof(in));
    for (int i = 0; i < n; ++i) {
        a[i] = (int *) malloc((k + 1) * sizeof(int));
        for (int j = 0; j <= k; j++) {
            a[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &v, &s);
        b[i].ves = v;
        b[i].scet = s;
        int sc = 0;
        if (i != 0) {
            while (sc < v) {
                a[i][sc] = a[i - 1][sc];
                sc += 1;
            }
        }
        sc = 0;
        while (v + sc <= k) {
            if (i != 0) {
                a[i][v + sc] = max(s + a[i - 1][sc], a[i - 1][v + sc]);
                sc += 1;
            } else {
                a[i][v + sc] = s;
                sc += 1;
            }
        }
    }
//    printf("15");
    int scet = k, count = 0, ves = 0, stoim = 0, *c;
    c = (int *) malloc(n * sizeof(int));
    if (n != 1) {
        for (int i = n - 1; i > 0; i--) {
            c[i] = 0;
            if (a[i][scet] != a[i - 1][scet]) {
                count += 1;
                scet -= b[i].ves;
                stoim += b[i].scet;
                c[i] = i + 1;
                if (i == 1 && scet - b[i - 1].ves >= 0) {

                    count += 1;
                    scet -= b[i - 1].ves;
                    stoim += b[i - 1].scet;
                    c[i - 1] = i;
                }
            } else if (i == 1 && a[0][scet] == a[1][scet] && scet - b[i - 1].ves >= 0) {
                count += 1;
                scet -= b[i - 1].ves;
                stoim += b[i - 1].scet;
                c[i - 1] = i;
            }
        }
    } else {
        stoim = a[0][k];
        scet = k - b[0].ves;
        count = 1;
        c[0] = 1;
    }

//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j <= k; j++) {
//            printf("%d ", a[i][j]);
//        }
//        printf("\n");
//    }
    printf("%d %d %d\n", count, k - scet, stoim);
    for (int i = 0; i < n; i++) {
        if (c[i] != 0 && c[i] < 1000) {
            printf("%d ", c[i]);
        }
    }

}
#include <stdio.h>
#include<malloc.h>

//int is_empty_file(FILE *fp) {
//    int c = getc(fp);
//    if (c == EOF)
//        return 1;
//    ungetc(c, fp);
//    return 0;
//}
int good_res(char **a, int i, int j, int m, int n) {
    for (int k = j + 1; k <= m; k++) {
        if (a[i][k] == 'X') {
            return 0;
        }
    }
    for (int k = j - 1; k >= 0; k--) {
        if (a[i][k] == 'X') {
            return 0;
        }
    }
    for (int k = 0; k < n; k++) {
        if (a[k][j] == 'X') {
            return 0;
        }
    }
    for (int k = i; k > 0; k--) {
        if (a[k][j] == 'X') {
            return 0;
        }
    }
    int k = i;
    int g = j;
    while (k < n - 1 && g < m - 1) {
        k++;
        g++;

        if (a[k][g] == 'X') {
            return 0;
        }
    }
    k = i;
    g = j;
    while (k > 0 && g > 0) {
        k--;
        g--;
        if (a[k][g] == 'X') {
            return 0;
        }
    }
    k = i;
    g = j;
    while (k > 0 && g < m - 1) {
        k--;
        g++;
        if (a[k][g] == 'X') {
            return 0;
        }
    }
    k = i;
    g = j;
    while (k < n - 1 && g > 0) {
        k++;
        g--;
        if (a[k][g] == 'X') {
            return 0;
        }
    }
    return 1;
}

int Try(char **a, char **b, int i, int n, int m, FILE *out) {
    for (int j = 0; j < m; ++j) {
        if (a[i][j] == '?' && good_res(b, i, j, m, n) == 1) {
            b[i][j] = 'X';
            if (i + 1 != n) {
                Try(a, b, i + 1, n, m, out);
            } else {
                printf("YES\n");
                for (int e = 0; e < n; e++) {
                    for (int k = 0; k < m; k++) {

                        fprintf(out, "%c", b[e][k]);
                    }
                    fprintf(out, "\n");
                }
                return 1;
            }
            b[i][j] = '.';
        }


    }
    return 0;
}

int main() {
    FILE *out, *u;
    out = freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);
    char s;
    scanf("%c", &s);
    char **a = (char **) malloc(n * sizeof(char *));
    char **b = (char **) malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        a[i] = (char *) malloc(m * sizeof(char));
        b[i] = (char *) malloc(m * sizeof(char));
        for (int j = 0; j < m; j++) {
            scanf("%c", &a[i][j]);
            b[i][j] = '.';
        }
        scanf("%c", &s);
    }
    int k = 0;
    int y, flag = 0;
    flag = Try(a, b, k, n, m, out);
    fclose(out);
    FILE *out1 = freopen("output.txt", "r", stdin);

    char c;
    scanf("%c", &c);
    fclose(out1);
    if (c == 'Y') {
        return 0;
    } else {
        out = freopen("output.txt", "w", stdout);
        fprintf(out, "NO");
    }
}
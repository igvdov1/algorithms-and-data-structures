#include <stdio.h>


int main() {

    int n, mas[100] = {0};
    scanf("%d", &n);
    mas[0] = 0;
    mas[1] = 2;
    mas[2] = 3;
    for (int i = 3; i <= n; i++) {
        mas[i] = mas[i - 1] + mas[i - 2];
    }
    printf("%d", mas[n]);

}
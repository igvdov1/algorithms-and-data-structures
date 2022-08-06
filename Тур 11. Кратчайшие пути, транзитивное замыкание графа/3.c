// Program for transitive closure
// using Floyd Warshall Algorithm
#include<stdio.h>
#include <malloc.h>

void printSolution(int **reach, int n);

void Transit(int **mas, int n) {
    int **reach = (int **) malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        reach[i] = (int *) malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            reach[i][j] = mas[i][j];
        }
    }
    for (int k = 0; k < n; k++) {

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                reach[i][j] = reach[i][j] ||
                              (reach[i][k] && reach[k][j]);
            }
        }
    }
    printSolution(reach, n);
}

void printSolution(int **reach, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (i == j)
                printf("1");
            else
                printf("%d", reach[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, **mas, k;
    char tmp;
    scanf("%d", &n);
    mas = (int **) malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        mas[i] = (int *) malloc(sizeof(int) * n);
        scanf("%c", &tmp);
        for (int j = 0; j < n; j++) {
            scanf("%c", &tmp);
            mas[i][j] = tmp - 48;
        }
    }
    Transit(mas, n);
}
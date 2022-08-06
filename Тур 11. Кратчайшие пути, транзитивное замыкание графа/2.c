#include <stdio.h>
#include "malloc.h"

#define MAX 1111111


int adjlist[301][301] = {0}, deik[301][301] = {0}, v[301] = {0};
int end, weight, count, minindex, min, temp;
int ver[2];
struct list {
    int data;
    struct list *next;
};

typedef struct stack {
    struct list *top;
} Stack;

Stack *create() {
    Stack *S;
    S = (Stack *) malloc(sizeof(Stack));
    S->top = NULL;
    return S;
}

int empty(Stack *S) {
    return (S->top == NULL);
}

int pop(Stack *S) {
    int a;
    struct list *p;
    p = S->top;
    a = p->data;
    S->top = p->next;
    free(p);
    return a;
}

void push(Stack *S, int a) {
    struct list *p;
    p = (struct list *) malloc(sizeof(struct list));
    p->data = a;
    p->next = S->top;
    S->top = p;
}

void deikstra(int n) {
    for (int j = 0; j < (n + 1); ++j) {
        for (int i = 1; i < (n + 1); i++) {
            deik[j][i] = MAX;
            v[i] = 1;
        }
        deik[j][j] = 0;
        do {
            minindex = MAX;
            min = MAX;
            for (int i = 1; i < (n + 1); i++) {
                if ((v[i] == 1) && (deik[j][i] < min)) {
                    min = deik[j][i];
                    minindex = i;
                }
            }
            if (minindex != MAX) {
                for (int i = 1; i < (n + 1); i++) {
                    if (adjlist[minindex][i] > 0) {
                        temp = min + adjlist[minindex][i];
                        if (temp < deik[j][i]) {
                            deik[j][i] = temp;
                        }
                    }
                }
                v[minindex] = 0;
            }
        } while (minindex < MAX);
    }
}

void obr(Stack *stack, FILE *IN, int put, int n) {

    for (int j = 0; j < put; ++j) {
        fscanf(IN, "%d %d", &ver[0], &ver[1]);

        printf("%d ", deik[ver[0]][ver[1]]);

        end = ver[1];
        weight = deik[ver[0]][end];
        count = 1;

        while (end != ver[0]) {
            for (int i = 1; i < (n + 1); i++)
                if (adjlist[i][end] != 0) {
                    temp = weight - adjlist[i][end];
                    if (temp == deik[ver[0]][i]) {
                        weight = temp;
                        end = i;
                        count++;
                        push(stack, i);
                    }
                }
        }
        printf("%d ", count);
        while (!empty(stack)) {
            printf("%d ", pop(stack));
        }
        printf("%d", ver[1]);
        printf("\n");
    }
}

int main() {
    FILE *IN, *OUT;
    IN = freopen("input.txt", "r", stdin);
    int n, m, put, rast, ves, dop1, dop2;
    fscanf(IN, "%d %d %d %d", &n, &m, &put, &rast);


    for (int i = 0; i < m; ++i) {
        fscanf(IN, "%d %d %d", &dop1, &dop2, &ves);
        if (adjlist[dop1][dop2] == 0 || adjlist[dop1][dop2] > ves) {
            adjlist[dop1][dop2] = ves;
            adjlist[dop2][dop1] = ves;
        }
    }


    Stack *stack = create();

    deikstra(n);

    obr(stack, IN, put, n);

    for (int j = 0; j < rast; ++j) {
        fscanf(IN, "%d %d", &ver[0], &ver[1]);
        printf("%d\n", deik[ver[0]][ver[1]]);
    }


}
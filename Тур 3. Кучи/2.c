#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void siftDown(int *numbers, int root, int bottom) {
    int maxChild;
    int flag = 0;
    while ((root * 2 <= bottom) && (flag != 1)) {
        if (root * 2 == bottom) {
            maxChild = root * 2;
        } else if (numbers[root * 2] > numbers[root * 2 + 1]) {
            maxChild = root * 2;
        } else {
            maxChild = root * 2 + 1;
        }
        if (numbers[root] < numbers[maxChild]) {
            int temp = numbers[root];
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        } else {
            flag = 1;
        }
    }
}

void heapSort(int *numbers, int array_size) {
    for (int i = (array_size / 2); i >= 0; i--) {
        siftDown(numbers, i, array_size - 1);
    }
    for (int i = array_size - 1; i >= 1; i--) {
        swap(&numbers[0], &numbers[i]);
        siftDown(numbers, 0, i - 1);
    }
}

int main() {
    int *a;
    int n;
    scanf("%d", &n);
    a = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    heapSort(a, n);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
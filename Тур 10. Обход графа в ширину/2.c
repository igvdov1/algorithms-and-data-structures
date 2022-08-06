#include <stdio.h>
#include <malloc.h>

int i, j;

struct queue {
    int items[10001][2];
    int front;
    int rear;
};

struct queue *createQueue() {
    struct queue *q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

void enqueue(struct queue *q, int i, int j) {
    if (q->rear != 10000) {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear][0] = i;
        q->items[q->rear][1] = j;
    }
}

void dequeue(struct queue *q) {
    if (!(q->rear == -1)) {
        i = q->items[q->front][0];
        j = q->items[q->front][1];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
}

void func_1(char a[101][101], int b[101][101], int i, int j, struct queue *q, int cur_dist) {
    a[i][j] = '*';
    b[i][j] = cur_dist + 1;
    enqueue(q, i, j);
}

void bfs(char a[101][101], int b[101][101], int si, int sj, int M, int N) {
    struct queue *q = createQueue();
    int cur_dist;
    a[si][sj] = '*';
    b[si][sj] = 0;
    enqueue(q, si, sj);
    while (!(q->rear == -1)) {
        dequeue(q);
        cur_dist = b[i][j];
        if (i + 1 < M) {
            if ((a[i + 1][j] == '.') || (a[i + 1][j] == 'F')) {
                func_1(a, b, i + 1, j, q, cur_dist);
            }
        }
        if (j + 1 < N) {
            if ((a[i][j + 1] == '.') || (a[i][j + 1] == 'F')) {
                func_1(a, b, i, j + 1, q, cur_dist);
            }
        }
        if (i - 1 >= 0) {
            if ((a[i - 1][j] == '.') || (a[i - 1][j] == 'F')) {
                func_1(a, b, i - 1, j, q, cur_dist);
            }
        }
        if (j - 1 >= 0) {
            if ((a[i][j - 1] == '.') || (a[i][j - 1] == 'F')) {
                func_1(a, b, i, j - 1, q, cur_dist);
            }
        }
    }
}


int main() {
    int n, m;
    char c;
    scanf("%d %d", &n, &m);
    char f[101][101];
    int d[101][101], start[2], finish[2];
    for (i = 0; i < n; ++i) {
        scanf("%c", &c);
        for (j = 0; j < m; j++) {
            scanf("%c", &c);
            switch (c) {
                case 'S': {
                    start[0] = i;
                    start[1] = j;
                    break;
                }

                case 'F': {
                    finish[0] = i;
                    finish[1] = j;
                    break;
                }

            }
            d[i][j] = -1;
            f[i][j] = c;
        }
    }
    d[start[0]][start[1]] = 0;
    bfs(f, d, start[0], start[1], n, m);
    printf("%d", d[finish[0]][finish[1]]);
    return 0;
}


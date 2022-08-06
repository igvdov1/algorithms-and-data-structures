#include <stdio.h>
#include <stdlib.h>

struct Graph {
    int numVertices;
    int *color;
    int *depth;
    struct node **adjLists;
};
struct queue {
    int items[1000000];
    int front;
    int rear;
};
struct node {
    int vertex;
    struct node *next;
};

struct Graph *createGraph(int a) {
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numVertices = a;
    graph->adjLists = malloc(a * sizeof(struct node *));
    graph->color = malloc(a * sizeof(int));
    graph->depth = malloc(a * sizeof(int));
    return graph;
}

struct Graph *createDirectedGraph(int vertices) {
    struct Graph *graph = createGraph(vertices);
    for (int i = 0; i < vertices; ++i) {
        graph->adjLists[i] = NULL;
        graph->color[i] = 0;
        graph->depth[i] = -1;
    }
    return graph;
}

void addEdge(struct Graph *graph, int src, int a) {
    struct node *q = malloc(sizeof(struct node));
    q->vertex = a;
    q->next = NULL;
    q->next = graph->adjLists[src];
    graph->adjLists[src] = q;
}

int dequeue(struct queue *q) {
    int tmp;
    if (q->rear == -1) { //isEmpty
        tmp = -1;
    } else {
        tmp = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return tmp;
}

void enqueue(struct queue *q, int vertex) {
    if (q->rear != 1000000 - 1) { //enqueue
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = vertex;
    }//.
}

int isEmpty(struct queue *q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

void bfs(struct Graph *graph, int n) {
    int vertex = 0;
    struct queue *q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;

    graph->color[vertex] = 1;
    graph->depth[vertex] = 0;
    enqueue(q, vertex);

    while (!isEmpty(q)) { //isEmpty
        int currentVertex = dequeue(q);
        struct node *temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->color[adjVertex] == 0) {
                graph->color[adjVertex] = 1;
                graph->depth[adjVertex] = graph->depth[currentVertex] + 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;

        }
        graph->color[currentVertex] = 2;
    }
    for (int i = 0; i < n; ++i) {
        printf("%d\n", graph->depth[i]);
    }
}

int main() {
    int n, m, val_1, val_2;
    scanf("%d%d", &n, &m);
    struct Graph *graph = createDirectedGraph(n);

    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &val_1, &val_2);
        addEdge(graph, val_1 - 1, val_2 - 1);
    }

    bfs(graph, n);
    return 0;
}
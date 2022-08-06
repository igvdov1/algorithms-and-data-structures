#include <stdio.h>
#include "malloc.h"
#include "stdlib.h"


typedef struct Stack {
    int size;
    int top;
    int *arr;
} Stack;

Stack *create() {
    Stack *s;
    s = (Stack *) malloc(sizeof(Stack));
    s->top = 0;
    s->size = 1;
    s->arr = (int *) malloc(sizeof(int) * s->size);

    return s;
}

void makenull(Stack *S) {
    S->top = 0;
}

int empty(Stack *S) {
    return (S->top == 0);
}

int top(Stack *S) {
    return (S->arr[S->top - 1]);
}

int pop(Stack *S) {
    int a = S->arr[S->top - 1];
    S->top--;
    return a;
}

void push(Stack *S, int a) {
    if (S->top == S->size) {
        S->size *= 2;
        S->arr = (int *) realloc(S->arr, sizeof(int) * S->size);
    }
    S->arr[S->top++] = a;
}

typedef struct node {
    int vertex;
    struct node *next;
} Node;

Node *createNode(int v) {
    Node *newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

typedef struct Graph {
    int numVertices;
    int *visited;
    struct node **adjLists;
    int *prev;
} Graph;

struct Graph *createGraph(int vertices) {
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc((vertices + 1) * sizeof(struct node *));
    graph->visited = malloc((vertices + 1) * sizeof(int));
    graph->prev = malloc((vertices + 1) * sizeof(int));

    for (int i = 1; i <= vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
        graph->prev[i] = -1;
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    Node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void find_cycle(struct Graph *graph, int vertex) {
    graph->visited[vertex] = 2;
    struct node *adjList = graph->adjLists[vertex];
    struct node *temp = adjList;

    while (temp != NULL) {
        if (graph->visited[temp->vertex] == 0) {
            graph->prev[temp->vertex] = vertex;
            find_cycle(graph, temp->vertex);
        }
        if (graph->visited[temp->vertex] == 2) {
            Stack *ans = create();
            int final = temp->vertex, current = vertex;
            while (final != current) {
                push(ans, current);
                current = graph->prev[current];
            }
            printf("%d\n", ans->top + 1);
            while (!empty(ans)) {
                printf("%d ", pop(ans));
            }
            printf("%d ", final);
            exit(0);
        }
        temp = temp->next;
    }
    graph->visited[vertex] = 3;
}

int main() {
    int n, m, v1, v2;
    scanf("%d%d", &n, &m);
    Graph *graph = createGraph(n);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &v1, &v2);
        addEdge(graph, v1, v2);
    }
    for (int i = 1; i <= n; i++) {
        if (graph->visited[i] == 0) {
            find_cycle(graph, i);
        }
    }
    printf("-1");

    return 0;
}
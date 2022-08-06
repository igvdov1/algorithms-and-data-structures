#include <stdio.h>
#include <stdlib.h>

struct node {
    int vertex;
    struct node *next;
};


struct Graph {
    int numVertices;
    int *visited;

    struct node **adjLists;
};

void DFS(struct Graph *graph, int vertex, int *mas, int k) {
    struct node *adjList = graph->adjLists[vertex];
    struct node *temp = adjList;

    graph->visited[vertex] = 1;

    mas[vertex] = k;
    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex, mas, k);
        }
        temp = temp->next;
    }

}


struct node *createNode(int v) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}


struct Graph *createGraph(int vertices) {
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct node *));
    graph->visited = malloc(vertices * sizeof(int));
    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}


void addEdge(struct Graph *graph, int src, int dest) {
    struct node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

int main() {
    FILE *in, *out;
    in = freopen("input.txt", "r", stdin);
    out = freopen("output.txt", "w", stdout);
    int n, ver_1, ver_2, *mas, m, j = 0, count = 0;
    fscanf(in, "%d %d", &n, &m);
    struct Graph *graph = createGraph(n);
    mas = (int *) calloc(sizeof(int), n);
    while (fscanf(in, "%d %d", &ver_1, &ver_2) != EOF) {
        addEdge(graph, ver_1 - 1, ver_2 - 1);
    }
    for (int i = 0; i < n; i++) {
        if (mas[i] == 0) {
            count++;
            DFS(graph, i, mas, count);
        }
    }
    fprintf(out, "%d\n", count);

    for (int i = 0; i < n; i++) {
        fprintf(out, "%d ", mas[i]);
    }

}
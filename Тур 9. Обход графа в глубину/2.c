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

void DFS(struct Graph *graph, int vertex, int *mas) {
    struct node *adjList = graph->adjLists[vertex];
    struct node *temp = adjList;

    graph->visited[vertex] = 1;

    mas[vertex] = 2;
    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex, mas);
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


void printGraph(struct Graph *graph) {
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        struct node *temp = graph->adjLists[v];
        printf("%d\n ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    FILE *in;
    in = freopen("input.txt", "r", stdin);
    int n, ver_1, ver_2, *mas;
    fscanf(in, "%d", &n);
    struct Graph *graph = createGraph(n);
    mas = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        mas[i] = 0;
    }
    while (fscanf(in, "%d %d", &ver_1, &ver_2) != EOF) {
        addEdge(graph, ver_1 - 1, ver_2 - 1);
    }
    int count = 0;
    for (int i = 0; i < n; i++) {

        if (mas[i] == 0) {
            DFS(graph, i, mas);

            count++;
        }
    }
    if (count != 1) {
        printf("%d", count + 1);
    } else {
        printf("%d", count);
    }
    return 0;
}
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
int count = 0;

int DFS(struct Graph *graph, int vertex, int *mas) {
    struct node *adjList = graph->adjLists[vertex];
    struct node *temp = adjList;

    graph->visited[vertex] = 1;
    if (mas[vertex] == 1) {
        count += 1;
    }
    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex, mas);
        }
        temp = temp->next;
    }
    return count;
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
    int n, m, ver_1, ver_2, k, shams, *mas, j;
    int count = 0;
    scanf("%d %d", &n, &m);
    struct Graph *graph = createGraph(n);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &ver_1, &ver_2);
        addEdge(graph, ver_1 - 1, ver_2 - 1);
    }
    scanf("%d", &k);
    mas = (int *) malloc((n + 3) * sizeof(int));
    scanf("%d", &j);

    mas[j - 1] = 1;
    m = j - 1;
    for (int i = 1; i < k; i++) {
        scanf("%d", &j);
        mas[j - 1] = 1;
    }
    count = DFS(graph, m, mas);

    if (count >= k) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}
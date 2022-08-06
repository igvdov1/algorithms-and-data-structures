#include <stdio.h>
#include <stdlib.h>

typedef struct matr {
    int svyas;
    int number;
} matr;
matr eiler[21] = {0};
typedef struct nodes {
    int number;
    struct nodes *next;
} node;


typedef struct graph {
    int num_of_nodes;
    node **adj_list;
} Graph;


node *create_node(int num) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->next = NULL;
    new_node->number = num;
    return new_node;
}


Graph *create_graph(int num_of_nodes) {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->num_of_nodes = num_of_nodes;
    graph->adj_list = malloc((num_of_nodes + 1) * sizeof(node *));
    for (int i = 1; i <= num_of_nodes; ++i) {
        graph->adj_list[i] = NULL;
    }

    return graph;
}


void add_edge(Graph *graph, int node_1, int node_2) {
    node *p, *new_node = create_node(node_2);
    if (graph->adj_list[node_1] == NULL)
        graph->adj_list[node_1] = new_node;
    else {
        p = graph->adj_list[node_1];
        while (p->next != NULL)
            p = p->next;
        p->next = new_node;
    }

    new_node = create_node(node_1);

    if (graph->adj_list[node_2] == NULL)
        graph->adj_list[node_2] = new_node;
    else {
        p = graph->adj_list[node_2];

        while (p->next != NULL)
            p = p->next;
        p->next = new_node;

    }
}


typedef struct list {
    int data;
    struct list *next;
} list;


typedef struct stack {
    struct list *top;
} Stack;


Stack *Create() {
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

    if (p->next != NULL)
        S->top = p->next;
    else
        S->top = NULL;

    free(p);
    return a;
}


void push(Stack *S, int a) {
    list *p = (list *) malloc(sizeof(list));
    p->data = a;
    p->next = S->top;
    S->top = p;
}


void find_way(Stack *stack, Graph *graph, int vert) {
    push(stack, vert);
    int i = 0;
    while (!empty(stack)) {
        vert = stack->top->data;
        if (graph->adj_list[vert] == NULL) {

            eiler[i].svyas = vert;
            ++i;
            pop(stack);

        } else {
            node *p = graph->adj_list[vert];
            int next_vert = p->number;
            push(stack, next_vert);
            graph->adj_list[vert] = p->next;
            free(p);
            if (graph->adj_list[next_vert]->number == vert) {
                node *t = graph->adj_list[next_vert];
                graph->adj_list[next_vert] = t->next;
                free(t);

            } else {

                node *t = graph->adj_list[next_vert];

                while (t->next->number != vert)
                    t = t->next;
                node *q = t->next;
                t->next = q->next;


            }
        }
    }
}


int main() {
    int n, m, ver1, ver2;
    Stack *stack = Create();
    scanf("%d %d", &n, &m);
    int **adj_matrix = (int **) malloc(sizeof(int *) * (n + 1));
    for (int i = 0; i <= n; i++) {
        adj_matrix[i] = (int *) calloc(sizeof(int), (n + 1));
    }


    Graph *graph = create_graph(n);

    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &ver1, &ver2);
        add_edge(graph, ver1, ver2);
        adj_matrix[ver1][ver2] = i + 1;
        adj_matrix[ver2][ver1] = i + 1;
        eiler[ver1].number++;
        eiler[ver2].number++;
    }

    int count = 0;
    int node = 1;
    for (int i = 1; i <= n; ++i) {
        if (eiler[i].number % 2) {
            ++count;
            node = i;
        }
    }

    if (count == 0 || count == 2) {
        printf("YES\n");
        find_way(stack, graph, node);
        int i = 0;
        while (eiler[i + 1].svyas != 0) {
            printf("%d\n", adj_matrix[eiler[i].svyas][eiler[i + 1].svyas]);
            ++i;
        }
    } else
        printf("NO");

}
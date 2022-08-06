#include<stdio.h>
#include <string.h>
#include <malloc.h>
#include<ctype.h>

struct list {
    int data;
    struct list * next;
};
typedef struct stack {
    struct list *top;
} Stack;
Stack * create ( ){
    Stack * S;
    S = (Stack *) malloc (sizeof (Stack));
    S->top = NULL;
    return S;
}

int top (Stack *S){
    return (S->top->data);
}
int pop(Stack *S){
    int a;
    struct list *p;
    p = S->top;
    a = p->data;
    S-> top = p->next;
    free(p);
    return a;
}
void push(Stack *S, int a ){
    struct list *p;
    p = (struct list *) malloc ( sizeof (struct list));
    p->data = a;
    p->next = S-> top;
    S->top = p ;
}
int main(){
    Stack *s = create();
    int x, a, b;
    char y;
    char postfix[2000];
    gets(postfix);
    char *w = strtok(postfix, " ");
    while (w!=NULL){
        if(isalnum(w[0])){
            sscanf(w, "%d", &x);
            push(s, x);
        } else {
            y = w[0];
            switch (y) {
                case '+':
                    push(s, pop(s)+pop(s));
                    break;
                case '-':
                    a = pop(s);
                    b = pop(s);
                    push(s, b-a);
                    break;
                case '*':
                    push(s, pop(s)*pop(s));
                    break;
                case '/':
                    a = pop(s);
                    b = pop(s);
                    push(s, b/a);
                    break;
            }
        }
        w = strtok(NULL, " ");
    }
    printf("%d", top(s));
}
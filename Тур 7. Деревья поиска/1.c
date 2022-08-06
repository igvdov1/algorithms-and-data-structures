#include <stdio.h>
#include <malloc.h>

typedef struct node // структура для представления узлов дерева
{
    int key;
    unsigned char height;
    struct node *left;
    struct node *right;
} node;

unsigned char height(node *p) {
    return p ? p->height : 0;
}

int bfactor(node *p) {
    return height(p->right) - height(p->left);
}

void fixheight(node *p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

node *rotateright(node *p) // правый поворот вокруг p
{
    node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node *rotateleft(node *q) // левый поворот вокруг q
{
    node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node *balance(node *p) // балансировка узла p
{
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

node *insert(node *p, int k) // вставка ключа k в дерево с корнем p
{
    if (!p) {
        p = (node *) malloc(sizeof(node));
        p->key = k;
        p->left = NULL;
        p->right = NULL;
    } else {
        if (k < p->key)
            p->left = insert(p->left, k);
        else
            p->right = insert(p->right, k);
    }
    return balance(p);
}

node *findmin(node *p) // поиск узла с минимальным ключом в дереве p
{
    return p->left ? findmin(p->left) : p;
}

node *removemin(node *p) // удаление узла с минимальным ключом из дерева p
{
    if (p->left == 0)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

/*node *removess(node *p, int k) // удаление ключа k из дерева p
{
    if (!p) return 0;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else //  k == p->key
    {
        node *q = p->left;
        node *r = p->right;
        free(p);
        if (!r) return q;
        node *min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}*/

void inorder(node *root, FILE *out) {
    if (root != NULL) {
        inorder(root->left, out);
        fwrite(&root->key, sizeof(int), 1, out);
        inorder(root->right, out);
    }
}

int main() {
    int n, k;
    FILE *in, *out;
    in = fopen("input.bin", "rb");
    out = fopen("output.bin", "wb");

    fread(&n, sizeof(int), 1, in);
    node *d = NULL;
    for (int i = 0; i < n; i++) {
        fread(&k, sizeof(int), 1, in);
        d = insert(d, k);
    }
    inorder(d, out);
}
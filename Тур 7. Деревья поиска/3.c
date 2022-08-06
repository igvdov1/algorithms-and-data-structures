#include <stdio.h>
#include <malloc.h>
#include <math.h>

typedef struct node {
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

node *rotateright(node *p) {
    node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node *rotateleft(node *q) {
    node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node *balance(node *p) {
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
    return p;
}

node *insert(node *p, int k) {
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

node *findmin(node *p) {
    return p->left ? findmin(p->left) : p;
}

node *findmax(node *p) {
    return p->right ? findmax(p->right) : p;
}

node *removemin(node *p) // удаление узла с минимальным ключом из дерева p
{
    if (p->left == 0)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

node *removes(node *p, int k) {
    if (!p) return 0;
    if (k < p->key)
        p->left = removes(p->left, k);
    else if (k > p->key)
        p->right = removes(p->right, k);
    else {
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
}

int search(node *p, int k) {
    if (!p) return 0;
    if (k < p->key) {
        if (p->left != NULL) {
            p = p->left;
            search(p, k);
        } else return 0;
    } else if (k > p->key) {
        if (p->right != NULL) {
            p = p->right;
            search(p, k);
        } else return 0;
    } else {
        return 1;
    }
}

int lower(node *p, int k) {
//    node *z = p;
//    if (!p) return pow(10, 10);
    if (k > p->key) {
        p = p->right;
//        lower(p, k);
        return p->key;
    }
    if (k < p->key) {
        p = p->left;
        return p->key;
    } else {
        return k;
    }

}

int inorder(node *root, int k, int j) {
    if (root != NULL) {
        if (k <= root->key) {
            j = root->key;
            j = inorder(root->left, k, j);
        }
        if (k > root->key) {
            j = inorder(root->right, k, j);
            return j;
        }
    }
    return j;
}

void outorder(node *root) {
    if (root != NULL) {
        outorder(root->left);
        printf("%d ", root->key);
        outorder(root->right);
    }
}

int main() {
    int n, k;
    FILE *in, *out;
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    fscanf(in, "%d", &n);
    node *d = NULL;

    for (int i = 0; i < n; i++) {
        char a[7] = {0};
        fscanf(in, "%s", a);

        fscanf(in, "%d", &k);
        if (a[0] == 'a') {
            if (search(d, k) == 0) {
                d = insert(d, k);
                fprintf(out, "added\n");
            } else {
                fprintf(out, "dupe\n");
            }
        } else if (a[0] == 'r') {
            if (search(d, k) == 0) {
                fprintf(out, "miss\n");
            } else {
                d = removes(d, k);
                fprintf(out, "removed\n");
            }
        } else {
            if (d != NULL && findmax(d)->key >= k) {
                int j = 0;
                fprintf(out, "%d\n", inorder(d, k, j));
            } else {
                fprintf(out, "###\n");
            }
        }
    }

}
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef int key_t;
typedef unsigned int value_t;

typedef struct {
    key_t key;
    value_t value;
} pair_t;

typedef struct {
    pair_t *data;
    unsigned int size;
    unsigned int data_size;
} bheap_t;

bheap_t *
bheap_new(unsigned int initial_data_size) {
    bheap_t *h = (bheap_t *) malloc(sizeof(bheap_t));
    h->data = (pair_t *) malloc(sizeof(pair_t) * (1 + initial_data_size));
    h->data_size = 1 + initial_data_size;
    h->size = 0;
    return h;
}

void
bheap_delete(bheap_t *h) {
    if (h) {
        if (h->data) {
            free(h->data);
        }
        free(h);
    }
}

void
bheap_checkup(bheap_t *h, unsigned int c) {
    unsigned int p;
    for (p = c / 2; p > 0; c = p, p = c / 2) {
        if (h->data[p].key > h->data[c].key) {
            pair_t tmp = h->data[p];
            h->data[p] = h->data[c];
            h->data[c] = tmp;
        } else {
            break;
        }
    }
}

void
bheap_checkdown(bheap_t *h, unsigned int p) {
    unsigned int c;
    for (c = 2 * p; c <= h->size; p = c, c = 2 * p) {
        if (c + 1 <= h->size && h->data[c + 1].key < h->data[c].key) c++;
        if (h->data[c].key < h->data[p].key) {
            pair_t tmp;
            tmp = h->data[c];
            h->data[c] = h->data[p];
            h->data[p] = tmp;
        } else {
            break;
        }
    }
}


void
bheap_add(bheap_t *h, pair_t v) {
    if (h->size + 1 >= h->data_size) {
        h->data_size *= 2;
        h->data = (pair_t *) realloc(h->data, h->data_size * sizeof(pair_t));
    }
    h->data[++(h->size)] = v;
    bheap_checkup(h, h->size);
}

int
bheap_extract_min(bheap_t *h, pair_t *v) {
    if (h->size == 0) return 0;
    *v = h->data[1];
    h->data[1] = h->data[(h->size)--];
    bheap_checkdown(h, 1);
    return 1;
}

int main() {
    bheap_t *h = bheap_new(1000);
    int n, i;
    pair_t v = {0, 0};

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        char mass[10];
        scanf("%s", mass);
        if (mass[1] == 'u') {
            int k;
            scanf("%d", &k);
            v.key = k;
            v.value = i;
            bheap_add(h, v);
        } else {
            if (bheap_extract_min(h, &v) != NULL) {
                printf("%d\n", v.key);
            } else {
                printf("Heap is empty\n");
            }
        }
    }
    bheap_delete(h);
    return 0;
}
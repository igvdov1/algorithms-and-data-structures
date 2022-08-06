#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

#define hash_table_size 100001
struct htype {
    int index;
    int value;
    struct htype *next;
} primary[hash_table_size];

void creat_hash_map() {
    for (int i = 0; i < hash_table_size; i++) {
        primary[i].index = -1;
        primary[i].next = NULL;
    }
}

int get_hash(int number) {
    if (number < 0) {
        number = -number;
    }
    return number % hash_table_size;
}

void conflict_collision(struct htype *i, struct htype *start) {
    struct htype *old;
    old = start;
    while (start->next != NULL) {
        start = start->next;
        old = start;
    }
    old->next = i;
}

void store_hash(int value) {
    int hash = get_hash(value);
    struct htype *p;

    if (primary[hash].index == -1) {
        primary[hash].index = 0;
        primary[hash].value = value;
        return;
    }

    p = (struct htype *) malloc(sizeof(struct htype));
    p->index = 0;
    p->value = value;
    p->next = NULL;
    conflict_collision(p, &primary[hash]);
}

int find(int value) {
    int hash = get_hash(value);
    struct htype *p;

    if (primary[hash].index != -1 && primary[hash].value == value) {
        return 1;
    } else {
        p = &primary[hash];
        if (p->next == NULL) {
            return 0;
        } else {
            p = p->next;
            while (p->next != NULL) {
                if (p->value == value) {
                    return 1;
                }
                p = p->next;
            }
            if (p->value == value) {
                return 1;
            }
            return 0;
        }
    }
}

int main(void) {
    FILE *in, *out;
    in = fopen("input.bin", "rb");
    out = fopen("output.bin", "wb");

    creat_hash_map();
    int n, number, count = 0;

    fread(&n, sizeof(int), 1, in);
    int *mas = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        fread(&number, sizeof(int), 1, in);
        if (find(number) != 1) {
            store_hash(number);
            mas[count++] = number;
        }
    }

    fwrite(&count, sizeof(int), 1, out);
    for (int j = 0; j < count; ++j) {
        fwrite(&mas[j], sizeof(int), 1, out);
    }

}
#include <stdio.h>
#include <malloc.h>
#include <stdint.h>

#define hash_table_size 1000010
unsigned long long M, a, b, c;
struct htype {
    unsigned long long value;
    unsigned long long array_index;
    struct htype *next;
} primary[hash_table_size];

void creat_hash_map() {
    for (int i = 0; i < hash_table_size; i++) {
        primary[i].next = NULL;
        primary[i].array_index = -1;
    }
}

long long get_hash(unsigned long long number) {
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

void store_hash(unsigned long long value, unsigned long long i) {
    unsigned long long hash = get_hash(value);
    struct htype *p;

    if (primary[hash].array_index == -1) {
        primary[hash].value = value;
        primary[hash].array_index = i;
        return;
    }

    p = (struct htype *) malloc(sizeof(struct htype));
    p->value = value;
    p->array_index = i;
    p->next = NULL;
    conflict_collision(p, &primary[hash]);
}

unsigned long long find(unsigned long long value) {
    unsigned long long hash = get_hash(value);
    struct htype *p;

    if (primary[hash].array_index != -1 && primary[hash].value == value) {
        return primary[hash].array_index;
    } else {
        p = &primary[hash];
        if (p->next == NULL) {
            return -1;
        } else {
            p = p->next;
            while (p->next != NULL) {
                if (p->value == value) {
                    return p->array_index;
                }
                p = p->next;
            }
            if (p->value == value) {
                return p->array_index;
            }
            return -1;
        }
    }
}

unsigned long long func(long long pos) {
    return (pos * pos * a + pos * b + c) % M;
}

int main(void) {
    scanf("%llu %llu %llu %llu", &M, &a, &b, &c);
    creat_hash_map();
    unsigned long long start = 1, k = 1;
    int count = 0;

    while (1) {
        k = find(start);
        if (k == -1) {
            store_hash(start, count);
        } else {
            break;
        }
        count++;
        start = func(start);
    }
    printf("%llu %d", k, count);
}
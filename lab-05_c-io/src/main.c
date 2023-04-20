#include <stdio.h>
#include "point_list.h"
#include "clist.h"
#include "string.h"

#define RANK_SIZE 256
#define BYTES 3

int get_number_from_bytes(FILE *f) {
    int timed_number = 0;
    int rank = 1;
    int number = 0;
    for (int i = 0; i < BYTES; i++) {
        fread(&timed_number, sizeof(char), 1, f);
        number += timed_number * rank;
        rank *= RANK_SIZE;
    }
    return number;
}

void count(intrusive_node_t *node, void *data) {
    int *counter = (int *) data;
    (*counter)++;
}

void print(intrusive_node_t *node, void *data) {
    struct point *item = container_of(node,
                                      struct point, node);
    printf((char *) data, item->x, item->y);
}

int main(int argc, char *argv[]) {
    intrusive_list_t l;
    init_list(&l);
    FILE *file;
    int x, y;
    if (strcmp(argv[1], "loadtext") == 0) {
        file = fopen(argv[2], "r");
        while (fscanf(file, "%d %d", &x, &y) != EOF) {
            add_point(&l, x, y);
        }
    } else {
        file = fopen(argv[2], "rb");
        fseek(file, 0, SEEK_END);
        int size = ftell(file) / 6;
        fseek(file, 0, SEEK_SET);
        for (int i = 0; i < size; i++) {
            x = get_number_from_bytes(file);
            y = get_number_from_bytes(file);
            add_point(&l, x, y);
        }
    }
    if (strcmp(argv[3], "savetext") == 0) {
        write_to_file(&l, argv[4], write_to_text_file);
    } else if (strcmp(argv[3], "savebin") == 0) {
        write_to_file(&l, argv[4], write_to_bin_file);
    } else if (strcmp(argv[3], "count") == 0) {
        int counter = 0;
        apply(&l, count, &counter);
        printf("%d\n", counter);
    } else if (strcmp(argv[3], "print") == 0) {
        apply(&l, print, argv[4]);
        printf("\n");
    }
    remove_all_points(&l);
    return 0;
}
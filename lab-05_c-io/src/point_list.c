#include <stdlib.h>
#include <stdio.h>
#include "clist.h"
#include "point_list.h"
#define RANK_SIZE 256

void write_number_as_binary(FILE *file, int number) {
    int third_byte = number / (RANK_SIZE*RANK_SIZE);
    number -= third_byte * (RANK_SIZE*RANK_SIZE);
    int second_byte = number / (RANK_SIZE);
    number -= second_byte * (RANK_SIZE);
    int first_byte = number;
    fwrite(&first_byte, sizeof(char), 1, file);
    fwrite(&second_byte, sizeof(char), 1, file);
    fwrite(&third_byte, sizeof(char), 1, file);
}

void add_point(intrusive_list_t *list, int x, int y) {
    struct point *point_to_add = (struct point *) malloc(sizeof(struct point));
    point_to_add->x = x;
    point_to_add->y = y;
    add_node(list, &point_to_add->node);
}

void remove_all_points(intrusive_list_t *list) {
    intrusive_node_t *node = list->head;
    int length = get_length(list);
    for (int i = 0; i < length; i++) {
        struct point *item = container_of(node,
                                          struct point, node);
        node = node->next;
        remove_node(list, &item->node);
        free(item);
    }
}

void write_to_file(intrusive_list_t *list, char *name, void (*op)(FILE *file, int x, int y)) {
    FILE *file = fopen(name, "w");
    if (list->head) {
        intrusive_node_t *node = list->head->prev;
        int length = get_length(list);
        for (int i = 0; i < length; i++) {
            struct point *item = container_of(node,
                                              struct point, node);
            op(file, item->x, item->y);
            node = node->prev;
        }
    } else {
        fclose(file);
    }
}

void write_to_text_file(FILE *file, int x, int y) {
    fprintf(file, "%d %d\n", x, y);
}

void write_to_bin_file(FILE *file, int x, int y) {
    write_number_as_binary(file, x);
    write_number_as_binary(file, y);
}
#ifndef POINT_LIST_H
#define POINT_LIST_H

#include "clist.h"

struct point {
    int x, y;
    intrusive_node_t node;
};

void add_point(intrusive_list_t *list, int x, int y);

void remove_all_points(intrusive_list_t *list);

void write_to_file(intrusive_list_t *list, char *name, void (*op)(FILE *file, int x, int y));

void write_to_text_file(FILE *file, int x, int y);

void write_to_bin_file(FILE *file, int x, int y);

#endif

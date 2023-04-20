#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "clist.h"

struct point {
    int x, y;
    intrusive_node_t node;
};

void add_point(intrusive_list_t *list, int x, int y) {
    struct point *point_to_add = (struct point *) malloc(sizeof(struct point));
    point_to_add->x = x;
    point_to_add->y = y;
    add_node(list, &point_to_add->node);
}

void action_part_remove_point(intrusive_list_t *list, struct point *item, int x, int y, int length, int index) {
    if (item->x == x && item->y == y) {
        remove_node(list, &item->node);
        free(item);
    }
}

void action_part_remove_all_point(intrusive_list_t *list, struct point *item, int x, int y, int length, int index) {
    remove_node(list, &item->node);
    free(item);
}

void action_part_show_all_points(intrusive_list_t *list, struct point *item, int x, int y, int length, int index) {
    printf("(%d %d)", item->x, item->y);
    if (index != length - 1)
        printf(" ");
}

void iter_part(intrusive_list_t *list, int x, int y,
               void (action)(intrusive_list_t *list, struct point *item, int x, int y, int length, int index)) {
    intrusive_node_t *node = list->head;
    int length = get_length(list);
    for (int i = 0; i < length; i++) {
        struct point *item = container_of(node, struct point, node);
        node = node->next;
        action(list, item, x, y, length, i);
    }
}

void remove_point(intrusive_list_t *list, int x, int y) {
    iter_part(list, x, y, action_part_remove_point);
}

void show_all_points(intrusive_list_t *list) {
    iter_part(list, 0, 0, action_part_show_all_points);
    printf("\n");
}

void remove_all_points(intrusive_list_t *list) {
    iter_part(list, 0, 0, action_part_remove_all_point);
}

int main() {
    intrusive_list_t list;
    init_list(&list);
    char command[80];
    while (1) {
        scanf("%239s", command);
        if (strcmp(command, "add") == 0) {
            int a, b;
            scanf("%d %d", &a, &b);
            add_point(&list, a, b);
        } else if (strcmp(command, "rm") == 0) {
            int a, b;
            scanf("%d %d", &a, &b);
            remove_point(&list, a, b);
        } else if (strcmp(command, "rma") == 0) {
            remove_all_points(&list);
        } else if (strcmp(command, "len") == 0) {
            printf("%d\n", get_length(&list));
        } else if (strcmp(command, "print") == 0) {
            show_all_points(&list);
        } else if (strcmp(command, "exit") == 0) {
            remove_all_points(&list);
            break;
        } else {
            printf("Unknown command\n");
        }
    }
    return 0;
}

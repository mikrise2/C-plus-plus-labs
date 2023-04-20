#include "clist.h"

typedef struct intrusive_list intrusive_list_t;
typedef struct intrusive_node intrusive_node_t;

void init_list(intrusive_list_t *list) {
    list->head = NULL;
}

void add_node(intrusive_list_t *list, intrusive_node_t *new_node) {
    if (list->head) {
        intrusive_node_t *old_head = list->head;
        list->head = new_node;
        intrusive_node_t *old_head_cpy = old_head;
        old_head->prev = list->head;
        list->head->next = old_head;
        while (old_head->next != old_head_cpy) {
            old_head = old_head->next;
        }
        old_head->next = new_node;
        new_node->prev = old_head;

    } else {
        new_node->next = new_node;
        new_node->prev = new_node;
        list->head = new_node;
    }
}

void remove_node(intrusive_list_t *list, intrusive_node_t *node) {
    int length = get_length(list);
    if (length == 1) {
        list->head = NULL;
    } else if (length > 1) {
        intrusive_node_t *timed_node = list->head;
        while (timed_node != node)
            timed_node = timed_node->next;
        if (node == list->head)
            list->head = list->head->next;
        timed_node->next->prev = timed_node->prev;
        timed_node->prev->next = timed_node->next;
    }
}

int get_length(intrusive_list_t *list) {
    if (!list->head)
        return 0;
    intrusive_node_t *element = list->head;
    int size = 1;
    while (element->next != list->head) {
        element = element->next;
        size++;
    }
    return size;
}

void apply(intrusive_list_t *list, void (*op)(intrusive_node_t *node, void *data), void *data) {
    intrusive_node_t *node = list->head->prev;
    int length = get_length(list);
    for (int i = 0; i < length; i++) {
        op(node, data);
        node = node->prev;
    }
}
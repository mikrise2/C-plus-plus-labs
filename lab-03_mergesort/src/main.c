#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"


int int_gt_comparator(const void *a, const void *b) {
    return *(int *) b - *(int *) a;
}

int chr_gt_comparator(const void *a, const void *b) {
    return *(char *) b - *(char *) a;
}

int str_gt_comparator(const void *a, const void *b) {
    return strcmp(*(char **) b, *(char **) a);
}

int main(int argc, char *argv[]) {
    int size = argc - 2;
    void *array;
    if (strcmp(argv[1], "int") == 0) {
        array = malloc(size * sizeof(int));
        int *array_cpy = (int *) array;
        for (int i = 0; i < size; i++) {
            *array_cpy++ = atoi(argv[i + 2]);
        }
        mergesort(array, size, sizeof(int), int_gt_comparator);
    } else if (strcmp(argv[1], "char") == 0) {
        array = malloc(size * sizeof(char));
        char *array_cpy = (char *) array;
        for (int i = 0; i < size; i++) {
            *array_cpy++ = argv[i + 2][0];
        }
        mergesort(array, size, sizeof(char), chr_gt_comparator);
    } else if (strcmp(argv[1], "str") == 0) {
        array = malloc(size * sizeof(char *));
        char **array_cpy = (char **) array;
        for (int i = 0; i < size; i++) {
            *array_cpy++ = argv[i + 2];
        }
        mergesort(array, size, sizeof(char *), str_gt_comparator);
    }

    for (int i = 0; i < size; ++i) {
        if (strcmp(argv[1], "int") == 0)
            printf("%d", ((int *) (array))[i]);
        else if (strcmp(argv[1], "char") == 0)
            printf("%c", ((char *) (array))[i]);
        else if (strcmp(argv[1], "str") == 0)
            printf("%s", ((char **) (array))[i]);
        if (i != size - 1) {
            printf(" ");
        }
    }

    printf("\n");
    return 0;
}
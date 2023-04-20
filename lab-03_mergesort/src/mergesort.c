#include <stddef.h>
#include "mergesort.h"
#include "stdlib.h"

void swap(void *a1, void *a2, size_t element_size) {
    unsigned char *p = a1, *q = a2, tmp;
    for (size_t i = 0; i != element_size; ++i) {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}

void replace_all(void *array1, void *array2, size_t element_size, size_t elements) {
    unsigned char *p = array1, *q = array2;
    for (size_t i = 0; i < element_size * elements; ++i) {
        p[i] = q[i];
    }

}

void mergesort(void *array, size_t elements, size_t element_size,
               int (*comparator)(const void *, const void *)) {
    if (elements > 2) {
        mergesort(array, elements / 2, element_size, comparator);
        mergesort(array + element_size * (elements / 2), elements / 2 + elements % 2, element_size, comparator);
        void *array_first_part = array;
        void *array_first_part_cpy = array_first_part;
        void *array_second_part = array + element_size * (elements / 2);
        void *array_second_part_cpy = array_second_part;
        void *sorted_array = malloc(element_size * elements);
        void *sorted_array_cpy = sorted_array;
        for (int i = 0; i < elements; i++) {
            if ((array_first_part - array_first_part_cpy) / element_size >= elements / 2) {
                replace_all(sorted_array, array_second_part, element_size,1);
                array_second_part += element_size;
            } else if ((array_second_part - array_second_part_cpy) / element_size >= elements / 2 + elements % 2) {
                replace_all(sorted_array, array_first_part, element_size,1);
                array_first_part += element_size;
            } else {
                if (comparator(array_first_part, array_second_part) > 0) {
                    replace_all(sorted_array, array_first_part,
                                element_size,1);
                    array_first_part += element_size;
                } else {
                    replace_all(sorted_array, array_second_part,
                                element_size,1);
                    array_second_part += element_size;
                }
            }
            sorted_array += element_size;
        }
        replace_all(array, sorted_array_cpy, element_size, elements);
    } else if (elements == 2) {
        if (comparator(array, array + element_size) < 0) {
            swap(array, array + element_size, element_size);
        }
    }
}
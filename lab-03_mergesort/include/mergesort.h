#ifndef UNTITLED2_MERGESORT_H
#define UNTITLED2_MERGESORT_H

#include <stddef.h>

void swap(void *a1, void *a2, size_t element_size);

void replace_all(void *array1, void *array2, size_t element_size, size_t elements);

void mergesort(void *array, size_t elements, size_t element_size,
               int (*comparator)(const void *, const void *));

#endif
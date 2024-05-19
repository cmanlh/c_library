#include <stdlib.h>

typedef struct ArrayList
{
    size_t size;
    size_t capacity;
    size_t idx;

    size_t *items;
} ArrayList;

ArrayList ArrayListNew(int capacity);
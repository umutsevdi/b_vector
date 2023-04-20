#include "bvector.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int __BVECTOR_STATIC_COUNT(__bvector_static v)
{
    int c = 0;
    while (v) {
        if (v & 1)
            c++;
        v >>= 1;
    }
    return c;
}

bvector* bvector_new(uint64_t size)
{
    bvector* v = malloc(sizeof(bvector));
    v->nov = (size / __BVECTOR_STATIC_BOOL_COUNT) + (size % __BVECTOR_STATIC_BOOL_COUNT > 0);
    v->vectors = calloc(sizeof(__bvector_static), v->nov);
    v->point = 0;
    return v;
}

void bvector_free(bvector* vector)
{
    if (vector != NULL) {
        free(vector->vectors);
        free(vector);
    }
}

bvector* bvector_copy(bvector* vector)
{
    bvector* copy = bvector_new(vector->nov * __BVECTOR_STATIC_BOOL_COUNT);
    memcpy(vector->vectors, copy->vectors,
        vector->nov * sizeof(__bvector_static));
    copy->nov = vector->nov;
    return copy;
}

int bvector_get(bvector* vector, uint64_t index)
{
    uint64_t which = (index / __BVECTOR_STATIC_BOOL_COUNT) - (index % __BVECTOR_STATIC_BOOL_COUNT == 0);
    /* if the index is out of bounds*/
    if (which >= vector->nov) {
        return __BVECTOR_OUT_OF_BOUNDS;
    }
    return __BVECTOR_STATIC_GET(vector->vectors[which], index % __BVECTOR_STATIC_BOOL_COUNT);
}

int bvector_set(bvector* vector, uint64_t index, bool value)
{
    uint64_t which = (index / __BVECTOR_STATIC_BOOL_COUNT) - (index % __BVECTOR_STATIC_BOOL_COUNT == 0);
    /* if the index is out of bounds*/
    if (which >= vector->nov) {
        return __BVECTOR_OUT_OF_BOUNDS;
    }

    __BVECTOR_STATIC_SET(vector->vectors[which], index % __BVECTOR_STATIC_BOOL_COUNT, value);

    return 0;
}

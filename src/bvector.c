#include "bvector.h"
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
    v->point = size % __BVECTOR_STATIC_BOOL_COUNT;
    return v;
}

bvector* bvector_new_ones(uint64_t size)
{
    bvector* v = malloc(sizeof(bvector));
    v->nov = (size / __BVECTOR_STATIC_BOOL_COUNT) + (size % __BVECTOR_STATIC_BOOL_COUNT > 0);
    v->vectors = malloc(sizeof(__bvector_static) * v->nov);
    v->point = size % __BVECTOR_STATIC_BOOL_COUNT;

    int i = 0;
    for (; i < v->nov - 1; i++)
        v->vectors[i] = __BVECTOR_STATIC_ONES;
    v->vectors[v->nov - 1] = __BVECTOR_STATIC_ONE_GENERATE(
        v->point);
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

uint64_t bvector_count(bvector* vector)
{
    uint64_t count = 0;
    int i = 0;
    for (; i < vector->nov; i++)
        count += __BVECTOR_STATIC_COUNT(vector->vectors[i]);
    return count;
}

int bvector_compare(bvector* v1, bvector* v2)
{
    int neq = 0;
    if (v1->nov == v2->nov) {
        int i = 0;
        while (!neq && i < v1->nov) {
            if ((v1->vectors[i] & v2->vectors[2]) != __BVECTOR_STATIC_ONES)
                neq = 1;
            i++;
        }
    } else
        neq = v1->nov > v2->nov ? 1 : -1;
    return neq;
}

void bvector_apply(bvector* vector, bool (*fn)(bool))
{
    uint64_t i = 0;
    for (; i < vector->nov; i++) {
        uint64_t j = 0;
        for (; j < __BVECTOR_STATIC_BOOL_COUNT; j++) {
            __BVECTOR_STATIC_SET(vector->vectors[i], j, fn(__BVECTOR_STATIC_GET(vector->vectors[i], j)));
        }
    }
}

void bvector_append(bvector* vector, uint64_t item_count)
{
    if ((item_count - vector->point) / __BVECTOR_STATIC_BOOL_COUNT) {
        item_count -= vector->point;
        uint64_t required_vectors = (item_count / __BVECTOR_STATIC_BOOL_COUNT)
            + (item_count % __BVECTOR_STATIC_BOOL_COUNT > 0);
        vector->vectors = realloc(vector->vectors,
            (vector->nov + required_vectors) * sizeof(__bvector_static));
        vector->point = item_count % __BVECTOR_STATIC_BOOL_COUNT;
        return;
    }
    vector->point += item_count;
}

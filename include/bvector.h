/******************************************************************************

 * File: bvector.h
 *
 * Author: Umut Sevdi
 * Created: 04/19/23
 * Description: b_dynamic includes dynamically allocated bitwise boolean array
 * so it can store more than requested values.
 *
*****************************************************************************/

#ifndef __BVECTOR__
#define __BVECTOR__
#include <stdbool.h>
#include <stdint.h>

#define __BVECTOR_OUT_OF_BOUNDS -1

/******************************************************************************
                             __BVECTOR_STATIC
*****************************************************************************/

/* A single bit vector instance */
typedef uint64_t __bvector_static;
/* How much boolean value can fit in a single bvector_static */
#define __BVECTOR_STATIC_BOOL_COUNT 64
/* A __bvector_static where all elements are 1 */
#define __BVECTOR_STATIC_ONES 0xFFFFFFFFFFFFFFFF
/* Generates a __bvector_static where __COUNT elements are 1 and rest is zero */
#define __BVECTOR_STATIC_ONE_GENERATE(__COUNT) \
    ((__BVECTOR_STATIC_ONES << (__COUNT)) - 1)

/* Returns the number of ones in the given static vector */
int __BVECTOR_STATIC_COUNT(__bvector_static v);

/* Returns the value at index of the static vector. Returns
 * __BVECTOR_OUT_OF_BOUNDS if the size is not within the bounds */
#define __BVECTOR_STATIC_GET(vector, index)                \
    (int)(index >= 0 && index < 64 ? (vector >> index) & 1 \
                                   : __BVECTOR_OUT_OF_BOUNDS)

/* Assings the value to the given index in the static vector */
#define __BVECTOR_STATIC_SET(vector, index, value)          \
    ((index) >= 0 && (index) < 64 ? ((vector)               \
         = ((vector) & ~(__BVECTOR_STATIC_ONES << (index))) \
             | ((uint64_t)(value) << (index)))              \
                                  : __BVECTOR_OUT_OF_BOUNDS)

/******************************************************************************
                              DYNAMIC BVECTOR
*****************************************************************************/

/* Dynamic bit vector instance */
typedef struct {
    /* number of vectors */
    int nov;
    /* array of vectors */
    __bvector_static* vectors;
    /*point shows where the last element is*/
    uint64_t point;
} bvector;

/* Allocates a new bit vector for given initial size.
 * All vectors are assigned to 0 on initialization. */
bvector* bvector_new(uint64_t size);
/* Allocates a new bit vector for given initial size,
 * where all values are assigned to 1 within the size */
bvector* bvector_new_ones(uint64_t size);
/* Safely frees the vector from the memory. */
void bvector_free(bvector* vector);
/* Returns a copy of the given vector */
bvector* bvector_copy(bvector* vector);
/** Returns the value of the index in the vector, returns
 * <bold>__BVECTOR_OUT_OF_BOUNDS</bold> if the index is outside the scope of
 * the vector. */
int bvector_get(bvector* vector, uint64_t index);
/* Assigns a new value to the selected index */
int bvector_set(bvector* vector, uint64_t index, bool value);
/* Counts the number of ones within the vector */
uint64_t bvector_count(bvector* vector);
/*
 * bvector_compare -compares the values of two vectors
 * returns:
 * - 0 if both vectors are identical
 * - 1 or -1 for whichever is greater by size
 * */
int bvector_compare(bvector* v1, bvector* v2);
/* Takes a function, applies to the vectors' each element */
void bvector_apply(bvector* vector, bool (*fn)(bool));
/* Increases the size of the bvector to fit the new items */
void bvector_append(bvector* vector, uint64_t item_count);

#endif // !__BVECTOR__

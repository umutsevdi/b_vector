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
#define __BVECTOR_STATIC_BOOL_COUNT 64

/* a single bit vector instance */
typedef uint64_t __bvector_static;

/* Returns the number of zeros in the given static vector */
int __BVECTOR_STATIC_COUNT(__bvector_static v);

/* Returns the value at index of the static vector. Returns
 * __BVECTOR_OUT_OF_BOUNDS if the size is not within the bounds */
#define __BVECTOR_STATIC_GET(vector, index)                \
    (int)(index >= 0 && index < 64 ? (vector >> index) & 1 \
                                   : __BVECTOR_OUT_OF_BOUNDS)

/* Assings the value to the given index in the static vector */
#define __BVECTOR_STATIC_SET(vector, index, value) \
    ((index) >= 0 && (index) < 64 ? ((vector)      \
         = ((vector) & ~(1ULL << (index)))         \
             | ((uint64_t)(value) << (index)))     \
                                  : __BVECTOR_OUT_OF_BOUNDS)

#define __BVECTOR_APPLY(vector, operator) (vector operator)

typedef struct {
    /* number of vectors */
    int nov;
    /* array of vectors */
    __bvector_static* vectors;
    /*point shows where the last element is*/
    uint64_t point;
} bvector;

typedef struct {
    uint64_t size;
    char* bytes;
} bvector_result;

/* Allocates a new bit vector for given initial size. */
bvector* bvector_new(uint64_t size);
/* Safely frees the vector from the memory. */
void bvector_free(bvector* vector);
/* Returns a copy of the given vector */
bvector* bvector_copy(bvector* vector);
/** Returns the value of the index in the vector, returns
 * <b>__BVECTOR_OUT_OF_BOUNDS</b> if the index is outside the scope of
 * the vector. */
int bvector_get(bvector* vector, uint64_t index);
/* Assigns a new value to the selected index */
int bvector_set(bvector* vector, uint64_t index, bool value);
/* Counts the number of zeros within the vector */
uint64_t bvector_count(bvector* vector);
/* Merges two vectors into v1 */
void bvector_join(bvector* v1, bvector* v2);
/* compares the values of two vectors */
void bvector_compare(bvector* v1, bvector* v2);
/* Takes a function, applies to the vectors' each element */
void bvector_apply(bvector* vector, bool (*)(bool));

#endif // !__BVECTOR__

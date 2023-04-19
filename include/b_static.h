/******************************************************************************

 * File: b_static.h
 *
 * Author: Umut Sevdi
 * Created: 04/19/23
 * Description: Static b_vector utilities
 *
*****************************************************************************/

#ifndef __BVECTOR_STATIC__
#define __BVECTOR_STATIC__
#include <stdint.h>

#define BVECTOR_STATIC_OUT_OF_BOUNDS -1

typedef uint64_t bvector_static;

/**
 * bvector_static_count - returns the number of zeros in the given static vector
 */
int bvector_static_count(bvector_static v)
{
    int c = 0;
    while (v) {
        if (v & 1)
            c++;
        v >>= 1;
    }
    return c;
}

/**
 * bvector_static_get - returns the result of the i'th element in v
 * @v - static vector to search
 * @i - index of the element
 * @return - result of the index
 * - BVECTOR_STATIC_OUT_OF_BOUNDS if the i is out of bounds of the uint64_t
 */
int bvector_static_get(bvector_static v, int i)
{
    if (i > 64 && i < 0)
        return BVECTOR_STATIC_OUT_OF_BOUNDS;
    return (v >> i) & 1;
}

#endif // !__BVECTOR_STATIC__

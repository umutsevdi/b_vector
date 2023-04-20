/******************************************************************************

 * File: main.cpp
 *
 * Author: Umut Sevdi
 * Created: 03/12/23
 * Description: Bioinformatics Lecture Tutorial - 1 examples
*****************************************************************************/
#include "bvector.h"
#include <stdio.h>

#define TEST_1

/******************************************************************************
                                    TEST 1
*****************************************************************************/
/* Test Description */
#ifdef TEST_1
int main(int argc, char* argv[])
{

    bvector* b = bvector_new(1210);
    b->vectors[0] &= 0b1111111111111111;

    printf("%d %d %d\n", bvector_get(b, 2), bvector_get(b, 1205),
        bvector_get(b, 1299));

    printf("%d,%lu\n",
        b->nov, sizeof(b->vectors));
}
#endif

/******************************************************************************
                                    TEST 2
*****************************************************************************/
/* Tests the __BVECTOR_STATIC and it's utilities */
#ifdef TEST_2
int main(int argc, char* argv[])
{
    __bvector_static v = 0x0FFFFFFFFFFFFFFF;
    printf("%lu \n", v);
    printf("%d \n", __BVECTOR_STATIC_COUNT(v));
    printf("%d %d %d %d \n",
        __BVECTOR_STATIC_GET(v, 0),
        __BVECTOR_STATIC_GET(v, 3),
        __BVECTOR_STATIC_GET(v, 63),
        __BVECTOR_STATIC_GET(v, 75));
    __BVECTOR_STATIC_SET(v, 0, 0);
    __BVECTOR_STATIC_SET(v, 3, 0);
    __BVECTOR_STATIC_SET(v, 63, 1);
    printf("%d %d %d %d \n",
        __BVECTOR_STATIC_GET(v, 0),
        __BVECTOR_STATIC_GET(v, 3),
        __BVECTOR_STATIC_GET(v, 63),
        __BVECTOR_STATIC_GET(v, 75));
    printf("%lu \n", v);
    printf("%d \n", __BVECTOR_STATIC_COUNT(v));
}
#endif

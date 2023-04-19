/******************************************************************************

 * File: b_dynamic.h
 *
 * Author: Umut Sevdi
 * Created: 04/19/23
 * Description: b_dynamic includes dynamically allocated bitwise boolean array
 * so it can store more than requested values.
 *
*****************************************************************************/

#ifndef __BVECTOR_DYNAMIC__
#define __BVECTOR_DYNAMIC__
#include "b_static.h"
#include <stdint.h>

typedef struct {
    bvector_static* v;
} bvector;

#endif // !__BVECTOR_DYNAMIC__

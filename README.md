# b_vector
Dynamic boolean vector implementation for C programming language.

## bvector_static
**bvector_static** is a 64-bit value that can store up to 64 different boolean
values.
It comes with the following functions and macros:

- **__BVECTOR_STATIC_BOOL_COUNT**:  How much boolean value can fit in a single
static vector.
- **__BVECTOR_STATIC_ONES**: A static bvector where all bits are 2.
- **__BVECTOR_STATIC_ONE_GENERATE(__COUNT)** Generates a __bvector_static whose
least significant __COUNT bit is 1 and rest is zero.
- `int __BVECTOR_STATIC_COUNT(__bvector_static v)`: Returns the number of ones
in the given static vector 
- **__BVECTOR_STATIC_GET(vector, index)**: Returns the value at the index of the
static vector. Returns **__BVECTOR_OUT_OF_BOUNDS** if the size is not within the
bounds.
- **__BVECTOR_STATIC_SET(vector, index, value)**: Assigns the value to the given
index in the static vector.

## bvector_dynamic
The **bvector** is a dynamic structure that can hold more than 64 boolean values.

```cpp
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
```

# LICENSE

```txt
MIT License

Copyright (c) 2023 Umut Sevdi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

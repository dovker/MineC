#pragma once

#include <stdlib.h>

#include "Engine/defines.h"

typedef struct DynamicArray
{
    size_t allocated;
    size_t count;
    u8 *data;
} DynamicArray;

//
// PUBLIC USE FUNCTIONS
//

DynamicArray dynamic_array_create();
void dynamic_array_free(DynamicArray* array); //Frees data pointer
void dynamic_array_clean(DynamicArray* array); //Keeps the allocated memory, but resets the count

//DON'T WANT TO BREAK THE C SYNTAX BUT WHAT CAN YOU DO ABOUT IT?
//WILL USE TYPEOF() WHEN IT BECOMES C STANDARD

#define dynamic_array_add(array, type, value) \
        *((type*)_dynamic_array_add_expand(array, sizeof(value))) = value

#define dynamic_array_insert(array, type, pos, value) \
        *((type*)_dynamic_array_insert_expand(array, pos, sizeof(value))) = value

#define dynamic_array_at(array, type, pos) \
        *(type*)_dynamic_array_at_position(array, pos, sizeof(type))    

#define dynamic_array_erase(array, type, pos, count) \
        _dynamic_array_erase(array, pos, count, sizeof(type))

#define dynamic_array_remove(array, type, pos) \
        _dynamic_array_remove(array, pos, sizeof(type))

//
// PRIVATE USE FUNCTIONS
//

void _dynamic_array_remove(DynamicArray* array, size_t pos, size_t size);
void _dynamic_array_erase(DynamicArray* array, size_t pos, size_t count, size_t size);

void* _dynamic_array_add_expand(DynamicArray* array, size_t size);
void* _dynamic_array_insert_expand(DynamicArray* array, size_t pos, size_t size);

void* _dynamic_array_at_position(DynamicArray* array, size_t pos, size_t size);
b8 _dynamic_array_has_space(DynamicArray* array);

void _reallocate_dynamic_array(DynamicArray* array, size_t size);

// EXAMPLE:

// DynamicArray vec = dynamic_array_create();
// int x = 989;
// dynamic_array_add(&vec, int, x);

// printf("Value at 0: %d\n", dynamic_array_at(&vec, int, 0)); //PRINTS 989
// dynamic_array_add(&vec, int, 78);
// dynamic_array_add(&vec, int, 99);
// MC_LOG("Count: %d\n", vec.count); //PRINTS 3

// dynamic_array_erase(&vec, int, 1, 2);
// MC_LOG("Count: %d\n", vec.count); //PRINTS 1

// dynamic_array_free(&vec); //deallocates data pointer
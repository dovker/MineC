#include "dynamic_array.h"

#include <stdlib.h>
#include <stdio.h>

DynamicArray dynamic_array_create()
{
	DynamicArray arr = { 0, 0, NULL };
	return arr;
}

b8 _dynamic_array_has_space(DynamicArray* array)
{
	return array->allocated - array->count > 0;
}

void dynamic_array_free(DynamicArray* array)
{
	free(array->data);
	array->allocated = 0;
	array->count = 0;
}

void dynamic_array_clean(DynamicArray* array)
{
	array->count = 0;
}

void _reallocate_dynamic_array(DynamicArray* array, size_t size)
{
	size_t new_alloc = (array->allocated == 0) ? 1 : array->allocated * 2;
	array->data = realloc(array->data, new_alloc * size);
	array->allocated = new_alloc;
}

void _dynamic_array_erase(DynamicArray* array, size_t pos, size_t count, size_t size)
{	
	memmove(&array->data[pos * size], &array->data[(pos + count) * size], (array->count - pos - count) * size);

	array->count -= count;
}

void _dynamic_array_remove(DynamicArray* array, size_t pos, size_t size)
{
	_dynamic_array_erase(array, pos, 1, size);
}

void* _dynamic_array_add_expand(DynamicArray* array, size_t size)
{
	if (!_dynamic_array_has_space(array))
	{
		_reallocate_dynamic_array(array, size);
	}

	void* ptr = array->data + (size * array->count);
	array->count++;
	return ptr;
}

void* _dynamic_array_insert_expand(DynamicArray* array, size_t pos, size_t size)
{
	size_t new_count = array->count + 1;

	if (!_dynamic_array_has_space(array))
	{
		_reallocate_dynamic_array(array, size);
	}
	memmove(&array->data[(pos + 1) * size], &array->data[pos * size], (array->count - pos) * size);

	array->count = new_count;

	return &array->data[pos * size];
}

void* _dynamic_array_at_position(DynamicArray* array, size_t pos, size_t size)
{
	MC_ASSERT(pos > array->count, "ELEMENT AT THIS POSITION DOESN'T EXIST!");
	return &array->data[pos * size];
}
#ifndef PROL_STACK
#define PROL_STACK

#include <stdlib.h>

typedef struct __prol_stack
{

	void *mem;
	size_t size,
		   capacity,
		   elem_size;
} prol_stack;

prol_stack new_prol_stack (size_t elem_size)
{

	prol_stack temp;
	temp.size = 0;
	temp.capacity = 100;
	temp.elem_size = elem_size;

	temp.mem = calloc(100, elem_size);

	return temp;
}

void clear_prol_stack (prol_stack *st)
{

	free(st->mem);
	st->size = 0;
	st->capacity = 0;
	st->elem_size = 0;
}

void *get_prol_stack (prol_stack *st, size_t num)
{

	return (char*)st->mem + num * st->elem_size;
}

void *back_prol_stack (prol_stack *st)
{

	return (char*)st->mem + (st->size - 1) * st->elem_size;
}

void pop_prol_stack (prol_stack *st)
{

	st->size--;
	if (st->size * 4 <= st->capacity)
	{

		void *temp = calloc(st->capacity / 2, st->elem_size);
		memcpy(temp, st->mem, st->elem_size * st->size);
		free(st->mem);
		st->mem  = temp;

		st->capacity /= 2;
	}
}

void pop_n_prol_stack (prol_stack *st, size_t n)
{

	for (int i = 0; i < n; ++i)
		pop_prol_stack(st);
}

void push_prol_stack (prol_stack *st, const void *elem_ptr)
{

	if (st->size >= st->capacity)
	{

		st->mem = realloc(st->mem, st->elem_size * st->capacity * 2);
		st->capacity *= 2;
	}

	memcpy((char*)st->mem + st->size * st->elem_size, elem_ptr, st->elem_size);
	st->size++;
}

void push_n_prol_stack (prol_stack *st, const void *elem_ptr, const size_t n)
{

	for (int i = 0; i < n; ++i)
	{

		push_prol_stack(st, elem_ptr);
		elem_ptr = (char*)elem_ptr + st->elem_size;
	}
}

void dump_prol_stack (prol_stack *st, FILE *out)
{

	fwrite(st->mem, st->elem_size, st->size, out);
}

#endif //PROL_STACK
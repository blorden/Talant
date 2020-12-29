#ifndef PROL_STACK
#define PROL_STACK

#include <stdlib.h>

enum prol_stack_settings
{

	PROL_STACK_START_CAPACITY = 100,
	PROL_STACK_MULTY_CAPACITY = 2,
	PROL_STACK_DEMULTY_MARK = 4
};

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
	temp.capacity = PROL_STACK_START_CAPACITY;
	temp.elem_size = elem_size;

	temp.mem = calloc(PROL_STACK_START_CAPACITY, elem_size);

	return temp;
}

void clear_prol_stack (prol_stack *st)
{

	assert(st);

	free(st->mem);
	st->size = 0;
	st->capacity = 0;
	st->elem_size = 0;
}

//get num element
void *get_prol_stack (prol_stack *st, size_t num)
{

	assert(st);

	return (char*)st->mem + num * st->elem_size;
}

//last stack element
void *back_prol_stack (prol_stack *st)
{

	assert(st);

	return (char*)st->mem + (st->size - 1) * st->elem_size;
}

//pop element
void pop_prol_stack (prol_stack *st)
{

	assert(st);

	st->size--;
	if (st->size * PROL_STACK_DEMULTY_MARK <= st->capacity)
	{

		void *temp = calloc(st->capacity / PROL_STACK_MULTY_CAPACITY, st->elem_size);
		memcpy(temp, st->mem, st->elem_size * st->size);
		free(st->mem);
		st->mem  = temp;

		st->capacity /= PROL_STACK_MULTY_CAPACITY;
	}
}

//pop n elements
void pop_n_prol_stack (prol_stack *st, size_t n)
{

	assert(st);

	for (int i = 0; i < n; ++i)
		pop_prol_stack(st);
}

//add element
void push_prol_stack (prol_stack *st, const void *elem_ptr)
{

	assert(st);

	if (st->size >= st->capacity)
	{

		st->mem = realloc(st->mem, st->elem_size * st->capacity * PROL_STACK_MULTY_CAPACITY);
		st->capacity *= PROL_STACK_MULTY_CAPACITY;
	}

	memcpy((char*)st->mem + st->size * st->elem_size, elem_ptr, st->elem_size);
	st->size++;
}

//add n elements
void push_n_prol_stack (prol_stack *st, const void *elem_ptr, const size_t n)
{

	assert(st);

	for (int i = 0; i < n; ++i)
	{

		push_prol_stack(st, elem_ptr);
		elem_ptr = (char*)elem_ptr + st->elem_size;
	}
}

//write stack elements in file
void dump_prol_stack (prol_stack *st, FILE *out)
{

	assert(st);

	fwrite(st->mem, st->elem_size, st->size, out);
}

//sort stack elements
void sort_prol_stack (prol_stack *st,
					  int (*cmp)(const void *, const void *))
{

	assert(st);

	qsort(st->mem, st->size, st->elem_size, cmp);
}

#endif //PROL_STACK
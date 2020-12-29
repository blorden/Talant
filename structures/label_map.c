#ifndef LABEL_MAP
#define LABEL_MAP

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

enum label_map_settings
{

	LABEL_MAP_START_CAPACITY = 100,
	LABEL_MAP_MULTY_CAPACITY = 2
};


typedef struct __label_map
{

	char **mem;
	long long *labels;

	size_t size,
		   capacity;
} label_map;

label_map new_label_map ()
{

	label_map temp;
	temp.mem = (char**) calloc(LABEL_MAP_START_CAPACITY, sizeof(char*));
	temp.labels = (long long*) calloc(LABEL_MAP_START_CAPACITY, sizeof(long long));

	temp.size = 0;
	temp.capacity = LABEL_MAP_START_CAPACITY;

	return temp;
}

//insert label
int insert_label_map (label_map *st, char *str, long long byte_num)
{

	assert(st && str);

	for (int i = 0; i < st->size; ++i)
	{

		if (strlen(str) <= strlen(st->mem[i]))
			continue;

		if (strlen(str) - strlen(st->mem[i]) != 1)
			continue;



		size_t temp = strlen(st->mem[i]);
		bool not_equ = false;

		for (int j = 0; j < temp; ++j)
			if (st->mem[i][j] != str[j])
			{
				not_equ = true;
				break;
			}

		if (!not_equ)
			return -1;
	}

	if (st->size == st->capacity)
	{

		st->capacity *= LABEL_MAP_MULTY_CAPACITY;
		st->mem = (char**) realloc(st->mem, st->capacity * sizeof(char*));
		st->labels = (long long*) realloc(st->labels, st->capacity * sizeof(long long));
	}

	size_t temp_sz = strlen(str);

	char *temp = (char*) calloc(temp_sz + 1, 1);
	memcpy(temp, str, temp_sz + 1);
	temp[temp_sz - 1] = '\0'; //delete :

	st->mem[st->size] = temp;
	st->labels[st->size++] = byte_num;

	return 0;
}

bool exist_label_map (label_map *st, char *str)
{

	assert(st && str);

	for (int i = 0; i < st->size; ++i)
		if (strcmp(st->mem[i], str) == 0)
			return true;

	return false;
}

long long get_num_byte_label_map (label_map *st, char *str)
{

	assert(st && str);

	for (int i = 0; i < st->size; ++i)
		if (strcmp(st->mem[i], str) == 0)
			return st->labels[i];

	return 0;
}

void clear_label_map (label_map *st)
{

	assert(st);

	for (int i = 0; i < st->size; ++i)
		free(st->mem[i]);

	free(st->mem);
	free(st->labels);

	st->size = 0;
	st->capacity = 0;
}

#endif //LABEL_MAP
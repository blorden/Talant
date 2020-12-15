#ifndef STRSIZE
#define STRSIZE

#include <string.h>
#include <stdbool.h>
#include <assert.h>

/*
	This function return size str of byte
*/
size_t strsize (const char *str)
{

	assert(str);

	return (strlen(str) + 1) * sizeof(char);
}
#endif //STRSIZE
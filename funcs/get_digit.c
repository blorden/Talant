#ifndef GET_DIGIT
#define GET_DIGIT

#include <assert.h>
#include <stdlib.h>

/*
	This function return digit from asm file
*/
long long get_digit (const char *str)
{

	assert(str);

	return (long long)(atof(str) * 100);
}

#endif //GET_DIGIT
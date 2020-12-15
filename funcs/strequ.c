#ifndef STREQU
#define STREQU

#include <stdbool.h>
#include <assert.h>
#include <string.h>

bool strequ (const char *str1, const char *str2)
{

	assert(str1 && str2);

	return strcmp(str1, str2) == 0;
}

#endif //STREQU
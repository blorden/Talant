#ifndef IS_RAM
#define IS_RAM

#include <assert.h>
#include <stdbool.h>
#include <string.h>

bool is_ram (const char *str)
{

	assert(str);

	if (strlen(str) != 5)
		return false;

	if (str[0] != '[' || str[4] != ']')
		return false;

	if (str[1] != 'r' || str[3] != 'x')
		return false;

	return str[2] >= 'a' && str[2] <= 'u'; 
}

#endif //IS_RAM
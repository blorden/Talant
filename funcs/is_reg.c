#ifndef IS_REG
#define IS_REG

#include <stdbool.h>
#include <assert.h>

bool is_reg (char *str)
{

	assert(str);

	if (strlen(str) != 3)
		return false;

	return (str[0] == 'r' && str[2] == 'x' && 
		    (str[1] >= 'a' || str[1] <= 'u'));
}

#endif
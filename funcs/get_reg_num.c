#ifndef GET_REG_NUM
#define GET_REG_NUM

#include <assert.h>

long long get_reg_num (const char *str)
{

	assert(str);

	return str[1] - 'a';
}

#endif //GET_REG_NUM
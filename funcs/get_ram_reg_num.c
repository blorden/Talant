#ifndef GET_RAM_REG_NUM
#define GET_RAM_REG_NUM

#include <assert.h>

long long get_ram_reg_num (const char *str)
{

	assert(str);

	return str[2] - 'a';
}

#endif //GET_RAM_REG_NUM
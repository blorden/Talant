#ifndef IS_REG
#define IS_REG

#include "strequ.c"

#include <stdbool.h>
#include <assert.h>

//reg or not
bool is_reg (const char *str)
{

	assert(str);

#define REG(reg, num)      \
	if (strequ(#reg, str)) \
		return true;

#include "../code_gen/reg_gen.c"

#undef REG

	return false;
}

#endif
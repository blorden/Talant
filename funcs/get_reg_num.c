#ifndef GET_REG_NUM
#define GET_REG_NUM

#include "strequ.c"

#include <assert.h>

//this func return reg num
long long get_reg_num (const char *str)
{

	assert(str);

#define REG(reg, num) 		\
	if (strequ(#reg, str))	\
		return num;
//---------------------------

#include "../code_gen/reg_gen.c"

#undef REG

	assert(false);
}

#endif //GET_REG_NUM
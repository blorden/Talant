#ifndef GET_REG_NAME
#define GET_REG_NAME

//return register name 
const char* get_reg_name (unsigned char num_reg)
{

	const char *reg_name = NULL;

#define REG(reg, num) 			\
	if (num == num_reg)			\
		reg_name = #reg;
//-------------------------------

#include "../code_gen/reg_gen.c"

#undef REG

	return reg_name;
}

#endif //GET_REG_NAME
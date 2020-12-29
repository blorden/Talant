#ifndef GET_RAM_REG_NUM
#define GET_RAM_REG_NUM

#include "get_reg_num.c"

#include <assert.h>
#include <string.h>

/*
	This func return num of reg in ram
*/
long long get_ram_reg_num (char *str)
{

	assert(str);

	size_t ram_str_len = strlen(str);
	str[ram_str_len - 1] = '\0';					//] -> 0

	long long reg_num = get_reg_num(str + 1);		//[ r a x \0
													//  ^
													//  |

	str[ram_str_len - 1] = ']';						//0 -> ]

	return reg_num;
}

#endif //GET_RAM_REG_NUM
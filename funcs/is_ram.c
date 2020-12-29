#ifndef IS_RAM
#define IS_RAM

#include "is_reg.c"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

//check ram or not
bool is_ram (char *str)
{

	assert(str);

	size_t ram_str_len = strlen(str);

	if (str[0] != '[' || str[ram_str_len - 1] != ']')
		return false;

	str[ram_str_len - 1] = '\0';			//] -> 0

	bool is_reg_in_ram = is_reg(str + 1);   //[ r a x \0
											//  ^
											//  |

	str[ram_str_len - 1] = ']';				//0 -> ]

	return is_reg_in_ram;
}

#endif //IS_RAM
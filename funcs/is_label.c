#ifndef IS_LABEL
#define IS_LABEL

#include <stdbool.h>

bool is_label (char *str)
{

	assert(str);

	if (strlen(str) == 0)
		return false;
	
	return str[strlen(str) - 1] == ':';
}

#endif //IS_LABEL
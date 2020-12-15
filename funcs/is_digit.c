#ifndef IS_DIGIT
#define IS_DIGIT

#include <stdbool.h>
#include <assert.h>

bool __is_long (const char *str)
{

	assert(str);

	size_t len = strlen(str);
	for (int i = 0; i < len; ++i)
	{

		if (i == 0 && str[i] == '-')
			continue;

		if (str[i] >= '0' && str[i] <= '9')
			continue;
		else
			return false;
	}

	if (str[0] == '-' && len > 15)
		return false;
	else if (len > 14 && str[0] != '-')
		return false;

	return true;	
}

bool __is_double (const char *str)
{

	assert(str);

	size_t len = strlen(str);
	bool dot = false;
	size_t count_until_dot = 0;

	for (int i = 0; i < len; ++i)
	{

		if (i == 0 && str[i] == '-')
			continue;

		if (str[i] == '.')
		{

			if (dot)
				return false;
			dot = true;
			continue;
		}

		if (!dot)
			count_until_dot++;

		if (str[i] >= '0' && str[i] <= '9')
			continue;

		return false;
	}

	if (count_until_dot > 14)
		return false;

	return true;
}

bool is_digit (const char *str)
{

	return __is_long(str) || __is_double(str);
}

#endif //IS_DIGIT
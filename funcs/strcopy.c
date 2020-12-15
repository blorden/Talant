#ifndef STRCOPY
#define STRCOPY

#include "strsize.c"

char* strcopy (const char *str, char **buf, size_t *buf_sz)
{

	assert(buf);
	size_t cur_str_size = strsize(str);

	if (!*buf)
	{

		*buf_sz = cur_str_size;
		*buf = (char*) calloc(cur_str_size, sizeof(char));
	}


	if (*buf_sz < cur_str_size)
	{

		*buf    = realloc(*buf, 2*cur_str_size);
		*buf_sz = 2*cur_str_size;
	}

	memcpy(*buf, str, cur_str_size * sizeof(char));

	return *buf;
}

#endif //STRCOPY
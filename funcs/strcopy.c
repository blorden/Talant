#ifndef STRCOPY
#define STRCOPY

#include "strsize.c"

//copy string and return buf
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

		*buf    = realloc(*buf, SIZE_MULTIPLY*cur_str_size);
		*buf_sz = SIZE_MULTIPLY*cur_str_size;
	}

	memcpy(*buf, str, cur_str_size * sizeof(char));

	return *buf;
}

#endif //STRCOPY
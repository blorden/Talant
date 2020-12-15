#ifndef FILE_PARSER
#define FILE_PARSER

#include <assert.h>
#include <stdbool.h>

typedef struct __file_parser
{

	char *cur_str;
	size_t cur_str_len;
	bool file_end;
} file_parser;

file_parser new_file_parser (char *buf)
{

	file_parser temp;
	temp.cur_str = buf;

	int i = 0;
	while (true)
	{

		if (temp.cur_str[i] == '\n' || temp.cur_str[i] == '\0')
		{

			if (temp.cur_str[i] == '\0')
				temp.file_end = true;
			else
				temp.file_end = false;

			temp.cur_str[i] = '\0';
			temp.cur_str_len = i;

			break;
		}

		++i;
	}

	return temp;
}

char* next_file_parser (file_parser *st)
{

	assert(st);

	if (st->file_end)
		return NULL;

	int i = 0;
	st->cur_str[st->cur_str_len] = '\n';
	st->cur_str += st->cur_str_len + 1;

	while (true)
	{

		if (st->cur_str[i] == '\n' || st->cur_str[i] == '\0')
		{

			if (st->cur_str[i] == '\0')
				st->file_end = true;

			st->cur_str[i] = '\0';
			st->cur_str_len = i;
			break;
		}

		++i;
	}

	return st->cur_str;
}

char* cur_file_parser (file_parser *st)
{

	assert(st);

	return st->cur_str;
}

size_t cur_len_file_parser (file_parser *st)
{

	assert(st);

	return st->cur_str_len;
}

void clear_file_parser (file_parser *st)
{

	assert(st);

	if (!st->file_end)
		st->cur_str[st->cur_str_len] = '\n';

	st->cur_str = NULL;
	st->file_end = false;
	st->cur_str_len = 0;
}

#endif //FILE_PARSER
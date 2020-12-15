#ifndef FILESIZE
#define FILESIZE

#include <stdio.h>

/*
	This funciton return size of file in bytes
*/
size_t filesize (FILE *file_ptr)
{

	assert(file_ptr);

	size_t file_size = 0;

	fseek(file_ptr, 0, SEEK_END);
	file_size = ftello(file_ptr);

	fseek(file_ptr, 0, SEEK_SET);

	return file_size;
}
#endif  //FILESIZE
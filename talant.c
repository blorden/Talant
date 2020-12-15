#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "funcs/strsize.c"
#include "asm/asm_file.c"
#include "exec/exec_byte_code.c"

//foo.asm -> foo.bin
void asm_file_name_to_bin_file_name (char *ams_file_name);

int main (const int argc, const char *argv[])
{

	assert(argc > 1);

	if (strcmp(argv[1], "asm") == 0)
	{

		assert(argc > 2);

		const char *asm_file_name = argv[2];

		const size_t asm_file_name_size = strsize(asm_file_name),
			   		 bin_file_name_size = asm_file_name_size; 


		char *bin_file_name = (char*) calloc(asm_file_name_size, 
											  sizeof(char)); 

		memcpy(bin_file_name, asm_file_name, 
			    sizeof(char) * bin_file_name_size);
		//In this moment, bin_file_name = asm_file_name

		asm_file_name_to_bin_file_name(bin_file_name);

		FILE *asm_file_ptr = fopen(asm_file_name, "r"),
			 *bin_file_ptr = fopen(bin_file_name, "wb");

		assert(asm_file_ptr && bin_file_ptr);

		asm_file(asm_file_ptr, bin_file_ptr);

		free(bin_file_name);

		fclose(asm_file_ptr);
		fclose(bin_file_ptr);
	}
	else if (strcmp(argv[1], "exec") == 0)
	{

		const char *bin_file_name = argv[2];
		FILE *bin_file_ptr = fopen(bin_file_name, "rb");

		assert(bin_file_ptr);

		exec_byte_code(bin_file_ptr);

		fclose(bin_file_ptr);
	}
	return 0;
}

void asm_file_name_to_bin_file_name (char *asm_file_name)
{

	const size_t asm_file_name_size = strsize(asm_file_name),
			   	 bin_file_name_size = asm_file_name_size;

	assert(bin_file_name_size >= 4);

	asm_file_name[bin_file_name_size - 1] = '\0';
	asm_file_name[bin_file_name_size - 2] = 'n';
	asm_file_name[bin_file_name_size - 3] = 'i';
	asm_file_name[bin_file_name_size - 4] = 'b';
}
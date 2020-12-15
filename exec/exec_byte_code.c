#ifndef EXEC_BYTE_CODE
#define EXEC_BYTE_CODE

#include "../funcs/filesize.c"
#include "../structures/prol_stack.c"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define DEF_CMD(cmd_name, cmd_num, cmd_size, args_count, arg_type, is_jump, execute_code) \
	if (cmd_bin_file_num == cmd_num)													  \
	{																					  \
																						  \
		execute_code																	  \
		if (!is_jump)																	  \
			cur_byte += cmd_size;														  \
	}																					  

/*
	This func execute byte code from bin_file
*/
void exec_byte_code (FILE *bin_file_ptr)
{

	assert(bin_file_ptr);

	size_t buf_byte_code_size = filesize(bin_file_ptr);
	char *buf_byte_code = (char*) calloc(buf_byte_code_size, sizeof(char));
	fread(buf_byte_code, sizeof(char), buf_byte_code_size, bin_file_ptr);

	prol_stack exec_stack    = new_prol_stack(sizeof(char)),
			   ret_stack     = new_prol_stack(sizeof(long long));

	long long regs[30];

	long long *ram = NULL;
	size_t ram_sz  = 0;

	long long cmp_res = 0;
		   
	size_t cur_byte = 0;
	while (cur_byte < buf_byte_code_size)
	{

		unsigned char cmd_bin_file_num = buf_byte_code[cur_byte];

#include "../code_gen/code_gen.c"
	} 

	free(buf_byte_code);

	clear_prol_stack(&exec_stack);
	clear_prol_stack(&ret_stack);

	free(ram);
}

#undef DEF_CMD
#endif //EXEC_BYTE_CODE
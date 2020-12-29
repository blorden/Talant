#ifndef EXEC_BYTE_CODE
#define EXEC_BYTE_CODE

#include "commands_exec_def.c"

#include "../funcs/filesize.c"
#include "../structures/prol_stack.c"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>

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

	const size_t regs_count = MAX_REGS_COUNT;
	long long *regs = calloc(regs_count, sizeof(long long));

	const size_t bin_file_args_count = MAX_DSL_ARGS;
	long long *bin_file_args = calloc(bin_file_args_count, sizeof(long long));
	double double_digit = 0;
	long long ret_byte = 0;

	long long *ram = NULL;
	size_t ram_sz  = 0,
		   ram_num = 0;

	long long cmp_res = 0;
		   
	size_t cur_byte = 0;
	while (cur_byte < buf_byte_code_size)
	{

#define DEF_CMD(cmd_name, cmd_num, cmd_size, args_count, arg_type, is_jump, execute_code) 	  \
		if (cmd_bin_file_num == cmd_num)													  \
		{																					  \
																							  \
			execute_code																	  \
			if (!is_jump)																	  \
				cur_byte += cmd_size;														  \
		}																					  
//---------------------------------------------------------------------------------------------

	unsigned char cmd_bin_file_num = buf_byte_code[cur_byte];

#include "../code_gen/code_gen.c"
	} 

	free(buf_byte_code);

	clear_prol_stack(&exec_stack);
	clear_prol_stack(&ret_stack);

	free(ram);
	free(regs);
	free(bin_file_args);
}

#undef DEF_CMD
#endif //EXEC_BYTE_CODE
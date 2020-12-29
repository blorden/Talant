#ifndef DISASM_BYTE_CODE
#define DISASM_BYTE_CODE

#include "disasm_helper.c"
#include "../structures/prol_stack.c"
#include "../funcs/filesize.c"
#include "../funcs/get_reg_name.c"
#include "../structures/label_list.c"

#include <assert.h>
#include <stdlib.h>
 
void disasm_byte_code (FILE *bin_file_ptr, FILE *disasm_file_ptr)
{

	assert(bin_file_ptr && disasm_file_ptr);

	prol_stack labels_bytes = new_prol_stack(sizeof(long long));
	long long cur_label_name = 0;

	size_t buf_byte_code_size = filesize(bin_file_ptr);
	char *buf_byte_code = (char*) calloc(buf_byte_code_size, sizeof(char));
	fread(buf_byte_code, sizeof(char), buf_byte_code_size, bin_file_ptr);

	long long cur_byte = 0;

	//ll - label list
	label_list ll = new_label_list();

	//check jumps and keep label bytes
	while (cur_byte < buf_byte_code_size)
	{

		unsigned char cmd_bin_file_num = buf_byte_code[cur_byte];

#define DEF_CMD(cmd_name, cmd_num, cmd_size, args_count, arg_type, is_jump, execute_code) 	  \
		if (cmd_bin_file_num == cmd_num)													  \
		{																					  \
																							  \
			if (is_jump && args_count == 1)													  \
				push_prol_stack(&labels_bytes, (buf_byte_code + cur_byte + 1));				  \
																							  \
			cur_byte += cmd_size;															  \
		}																					  
//---------------------------------------------------------------------------------------------

#include "../code_gen/code_gen.c"

#undef DEF_CMD
	}

	//sort label bytes
	sort_prol_stack(&labels_bytes, __cmp_for_qsort_disasm);

	//create label list with sort label bytes
	for (int i = labels_bytes.size - 1; i >= 0; --i)
		if (i == labels_bytes.size - 1 || 
			(*(long long*)get_prol_stack(&labels_bytes, i) != 
			 *(long long*)get_prol_stack(&labels_bytes, i + 1)))
		{

			insert_label_list(&ll, cur_label_name++, *(long long*)get_prol_stack(&labels_bytes, i));
		}

	cur_label_name = 0;

	prol_stack disasm_lines_stack = new_prol_stack(sizeof(char));

	char *buf_add_line = NULL;
	size_t buf_add_line_size = 0;

	cur_byte = 0;

	while (cur_byte < buf_byte_code_size)
	{

		//check if need write label
		if (labels_bytes.size > 0 && 
			*(long long*)back_prol_stack(&labels_bytes) == cur_byte)
		{

			if (buf_add_line_size < 3)
			{

				buf_add_line_size = SIZE_MULTIPLY*buf_add_line_size + CONSTANT_ADD_SIZE;
				buf_add_line = realloc(buf_add_line, buf_add_line_size);
			}

			sprintf(buf_add_line, "#%lld:\n"
								  "\n", cur_label_name++);
			push_n_prol_stack(&disasm_lines_stack, buf_add_line, strlen(buf_add_line));

			while (labels_bytes.size > 0 && 
				   *(long long*)back_prol_stack(&labels_bytes) == cur_byte)
			{

				pop_prol_stack(&labels_bytes);
			}

			continue;
		}

		unsigned char cmd_bin_file_num = buf_byte_code[cur_byte];

#define DEF_CMD(cmd_name, cmd_num, cmd_size, args_count, arg_type, is_jump, execute_code) \
		else if (cmd_bin_file_num == cmd_num)											  \
		{																				  \
																						  \
			disasm_byte_code_to_line(cmd_name, args_count, arg_type,					  \
								     &buf_add_line, &buf_add_line_size,					  \
								     buf_byte_code, cur_byte,							  \
								     &disasm_lines_stack, &ll);							  \
																						  \
			cur_byte += cmd_size;														  \
		}
//-----------------------------------------------------------------------------------------

		if (false)
		{}
#include "../code_gen/code_gen.c"

#undef DEF_CMD
#undef BUF_REALLOC
	}


	dump_prol_stack(&disasm_lines_stack, disasm_file_ptr);

	clear_prol_stack(&disasm_lines_stack);
	clear_prol_stack(&labels_bytes);
	clear_label_list(&ll);

	free(buf_byte_code);
	if (buf_add_line)
		free(buf_add_line);
}

#endif //DISASM_BYTE_CODE
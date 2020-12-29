#ifndef DISASM_HELPER
#define DISASM_HELPER

#include "../structures/label_list.c"
#include "../funcs/get_reg_name.c"

/*	
	This compare need to sort labels.
	min byte in back.
*/
int __cmp_for_qsort_disasm (const void *a, const void *b)
{

	long long first_label_byte  = *(long long*)a,
			  second_label_byte = *(long long*)b;

	if (first_label_byte > second_label_byte)
		return -1;

	if (first_label_byte < second_label_byte)
		return 1;

	return 0;
}

/*
	Realloc line buf if need.
*/
void buf_realloc (char **buf_add_line, size_t *buf_add_line_size, size_t new_size)
{

	if (*buf_add_line_size < new_size)
	{																
																	
		*buf_add_line_size = SIZE_MULTIPLY*new_size + CONSTANT_ADD_SIZE;						
		*buf_add_line = realloc(*buf_add_line, *buf_add_line_size);	
	}
}

void disasm_byte_code_to_line (char *cmd_name, int args_count, int arg_type, 
						 	   char **buf_add_line, size_t *buf_add_line_size, 
						 	   char *buf_byte_code, long long cur_byte,
							   prol_stack *disasm_lines_stack, label_list *ll)
{

	if (args_count == ZERO_ARG)
	{

		buf_realloc(buf_add_line, buf_add_line_size, strlen(cmd_name) + CONSTANT_ADD_SIZE);
		sprintf(*buf_add_line, "\t%s\n", cmd_name);
	}
	else if (args_count == ONE_ARG && arg_type == REGISTER)
	{

		const char *reg_name = get_reg_name(buf_byte_code[cur_byte + sizeof(unsigned char)]);
		buf_realloc(buf_add_line, buf_add_line_size, strlen(cmd_name) + strsize(reg_name) + CONSTANT_ADD_SIZE);
		sprintf(*buf_add_line, "\t%s %s\n", cmd_name, reg_name);
	}
	else if (args_count == ONE_ARG && arg_type == DIGIT)
	{

		double digit = ((double)(*(long long*)(buf_byte_code + cur_byte + sizeof(unsigned char)))) / DOUBLE_PART; 
		buf_realloc(buf_add_line, buf_add_line_size, strlen(cmd_name) + CONSTANT_ADD_SIZE);
		sprintf(*buf_add_line, "\t%s %.2lf\n", cmd_name, digit);
	}
	else if (args_count == ONE_ARG && arg_type == RAM)
	{

		const char *reg_name = get_reg_name(buf_byte_code[cur_byte + sizeof(unsigned char)]);
		buf_realloc(buf_add_line, buf_add_line_size, strlen(cmd_name) + strsize(reg_name) + CONSTANT_ADD_SIZE);
		sprintf(*buf_add_line, "\t%s [%s]\n", cmd_name, reg_name);	
	}
	else if (args_count == ONE_ARG && arg_type == LABEL)
	{

		buf_realloc(buf_add_line, buf_add_line_size, strlen(cmd_name) + CONSTANT_ADD_SIZE);
		sprintf(*buf_add_line, "\t%s #%lld\n", cmd_name, 							          
			    get_label_list(ll, *(long long*)(buf_byte_code + cur_byte + sizeof(unsigned char))));
	}

	push_n_prol_stack(disasm_lines_stack, *buf_add_line, strlen(*buf_add_line));
}

#endif //DISASM_HELPER
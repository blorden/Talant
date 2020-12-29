#ifndef ASM_PARS_HELPER
#define ASM_PARS_HELPER

#include <assert.h>

#include "../code_gen/enums.c"
#include "../funcs/strequ.c"
#include "../funcs/is_ram.c"
#include "../funcs/is_reg.c"
#include "../funcs/is_digit.c"
#include "../funcs/strcopy.c"
#include "../funcs/get_ram_reg_num.c"
#include "../funcs/get_reg_num.c"
#include "../funcs/get_digit.c"
#include "../structures/file_parser.c"
#include "../structures/prol_stack.c"
#include "../structures/label_map.c"

/*
	Check asm code line jump-line or not
*/
bool is_jump_line (char *first_lyr, char *second_lyr, char *last_lyr, 
					char *cmd_name, int args_count, int arg_type, int is_jump)
{

	assert(first_lyr && cmd_name);

	return args_count == ONE_ARG && is_jump && 
		   second_lyr &&                                   							  
		   strequ(cmd_name, first_lyr) && 											  
		   !last_lyr;
}

/*
	Check asm code line arg-line or not
*/
bool is_arg_line(char *first_lyr, char *second_lyr, char *last_lyr,								  
				  char *cmd_name, int args_count, int arg_type, int is_jump)
{

	assert(first_lyr && cmd_name);

	return strequ(cmd_name, first_lyr) && !last_lyr &&
			((args_count == ONE_ARG && second_lyr &&
			  ((arg_type == RAM && is_ram(second_lyr)) || (arg_type == DIGIT && is_digit(second_lyr)) || 
			  (arg_type  == REGISTER && is_reg(second_lyr)))) ||
			 (args_count == ZERO_ARG && !second_lyr));
}

/*
	Translate arg-line to byte code
*/
void translate_arg_line (prol_stack *asm_byte_code, char *second_lyr, int cmd_num)
{

	assert(asm_byte_code);

	unsigned char temp_cmd_num = cmd_num;
	push_prol_stack(asm_byte_code, &temp_cmd_num);

	if (second_lyr && is_reg(second_lyr))
	{

		unsigned char temp_reg_num = get_reg_num(second_lyr);
		push_prol_stack(asm_byte_code, &temp_reg_num);
	}
	else if (second_lyr && is_ram(second_lyr))
	{

		unsigned char temp_reg_num = get_ram_reg_num(second_lyr);
		push_prol_stack(asm_byte_code, &temp_reg_num);
	}
	else if (second_lyr && is_digit(second_lyr))
	{

		long long temp_digit = get_digit(second_lyr);
		push_n_prol_stack(asm_byte_code, &temp_digit, sizeof(long long));
	}
}

/*
	Translate jump-line to byte code
*/
void translate_jump_line (prol_stack *asm_byte_code, char *second_lyr, int cmd_num, label_map *lm)
{

	assert(asm_byte_code && second_lyr && lm);

	unsigned char temp_cmd_num = cmd_num;
	push_prol_stack(asm_byte_code, &temp_cmd_num);

	long long temp_label_byte = get_num_byte_label_map(lm, second_lyr);
	push_n_prol_stack(asm_byte_code, &temp_label_byte, sizeof(long long));	
}

/*
	Prepare cur asm code line to pars, use strtok
*/
void prepare_for_line_check_pars (char **cur_line_for_strtok, char **cur_line, 
								  char **first_lyr, char **second_lyr, char **last_lyr, 
								  char **buf_str_asm_line_for_strtok, char **buf_str_asm_line,
								  size_t *buf_str_asm_line_for_strtok_size, size_t *buf_str_asm_line_size,
								  file_parser *fp)
{

	assert(cur_line_for_strtok && cur_line &&
		   first_lyr && second_lyr && last_lyr && 
		   buf_str_asm_line_for_strtok && buf_str_asm_line &&
		   buf_str_asm_line_for_strtok_size && buf_str_asm_line_size &&
		   fp);

	*cur_line_for_strtok = strcopy(cur_file_parser(fp), 				 
								    buf_str_asm_line_for_strtok, 	     
								    buf_str_asm_line_for_strtok_size);	 
																				 
	*cur_line            = strcopy(cur_file_parser(fp), 				 
								    buf_str_asm_line, 					 
								    buf_str_asm_line_size);			 
																				 
	*first_lyr  = strtok(*cur_line_for_strtok, " \t"),					 
	*second_lyr = strtok(NULL,                 " \t"),					 
	*last_lyr   = strtok(NULL,                 " \t");					 
			 																	 
	if (*first_lyr && (*first_lyr)[0] == ';')									 
		*first_lyr = NULL;													 
			 																	 
	if (!*first_lyr || (*second_lyr && (*second_lyr)[0] == ';'))					 
		*second_lyr = NULL;													 
																				 
	if (!*second_lyr || (*last_lyr && (*last_lyr)[0] == ';'))					 
		*last_lyr = NULL;
}

#endif //ASM_PARS_HELPER
#ifndef ASM
#define ASM

#include <string.h>
#include <stdio.h>

#include "asm_pars_helper.c"

#include "../funcs/filesize.c"
#include "../funcs/is_reg.c"
#include "../funcs/is_label.c"
#include "../funcs/is_digit.c"
#include "../funcs/strcopy.c"
#include "../funcs/strequ.c"
#include "../funcs/get_digit.c"
#include "../funcs/get_reg_num.c"
#include "../funcs/is_ram.c"
#include "../funcs/get_ram_reg_num.c"

#include "../structures/prol_stack.c"
#include "../structures/label_map.c"
#include "../structures/file_parser.c"
#include "../structures/jump_list.c"

#include "../code_gen/enums.c"	

/*
	This func asm file to byte code

	asm_file_ptr file with asm code
	bin_file_ptr file with byte code
*/
void asm_file (FILE *asm_file_ptr, FILE *bin_file_ptr)
{

#define DEF_CMD(cmd_name, cmd_num, cmd_size, args_count, arg_type, is_jump, execute_code) \
	else if (is_jump_line(first_lyr, second_lyr, last_lyr, 								  \
						  cmd_name, args_count, arg_type, is_jump))  					  \
	{																					  \
																						  \
		add_jump_list(&jl, cur_line, second_lyr, cur_asm_line_num);						  \
		cur_byte_bin_format += cmd_size;												  \
		str_declareted = true;															  \
	}																					  \
	else if (is_arg_line(first_lyr, second_lyr, last_lyr,								  \
						 cmd_name, args_count, arg_type, is_jump))						  \
	{																					  \
																						  \
		cur_byte_bin_format += cmd_size;											      \
		str_declareted = true;															  \
	}
//-----------------------------------------------------------------------------------------

	size_t asm_file_size = filesize(asm_file_ptr);
	char *buf_str_of_asm_file = (char*) calloc(asm_file_size + 1, sizeof(char));

	fread(buf_str_of_asm_file, sizeof(char), asm_file_size + 1, asm_file_ptr);
	buf_str_of_asm_file[asm_file_size] = '\0';

	file_parser fp = new_file_parser(buf_str_of_asm_file);

	size_t cur_asm_line_num = 0;

	char  *buf_str_asm_line = NULL;
	size_t buf_str_asm_line_size = 0;

	char  *buf_str_asm_line_for_strtok = NULL;
	size_t buf_str_asm_line_for_strtok_size = 0;

	bool   can_asm = true;
	size_t cur_byte_bin_format = 0,
		   cur_byte_asm_file   = 0;

	label_map lm = new_label_map();
	jump_list jl = new_jump_list();

	char *cur_line_for_strtok = NULL,
	 *cur_line = NULL,
	 *first_lyr = NULL,
	 *second_lyr = NULL,
	 *last_lyr = NULL;

	while (true)
	{

		cur_asm_line_num++;

		prepare_for_line_check_pars(&cur_line_for_strtok, &cur_line, 
									&first_lyr, &second_lyr, &last_lyr, 
									&buf_str_asm_line_for_strtok, &buf_str_asm_line,
									&buf_str_asm_line_for_strtok_size, &buf_str_asm_line_size,
									&fp);

		bool str_declareted = false;

		if (!first_lyr)
			str_declareted = true;
		else if (first_lyr && !second_lyr && !last_lyr && is_label(first_lyr))
		{
			insert_label_map(&lm, first_lyr, cur_byte_bin_format);
			str_declareted = true;
		}
#include "../code_gen/code_gen.c"

		if (!str_declareted)
		{

			can_asm = false;													  	          
			printf("error: incorrect line\n"
				   "line number: %ld\n"
				   "%s\n"
				   "\n", 				          
		    	   cur_asm_line_num, cur_line);
		}

		if (next_file_parser(&fp) == NULL)
		{

			clear_file_parser(&fp);
			break;
		}
	}

#undef DEF_CMD

	check_jump_list(&jl, &lm, &can_asm);
	clear_jump_list(&jl);

	if (!can_asm)
	{

		printf("Can`t asm file.\n");

		clear_label_map(&lm);

		free(buf_str_asm_line_for_strtok);
		free(buf_str_asm_line);
		free(buf_str_of_asm_file);
		return;		
	}

	fp = new_file_parser(buf_str_of_asm_file);

	prol_stack asm_byte_code = new_prol_stack(sizeof(char));

#define DEF_CMD(cmd_name, cmd_num, cmd_size, args_count, arg_type, is_jump, execute_code) \
	else if (is_arg_line(first_lyr, second_lyr, last_lyr,								  \
						 cmd_name, args_count, arg_type, is_jump))						  \
	{																					  \
																						  \
		translate_arg_line(&asm_byte_code, second_lyr, cmd_num);						  \
	}																					  \
	else if (is_jump_line(first_lyr, second_lyr, last_lyr,								  \
						  cmd_name, args_count, arg_type, is_jump))						  \
	{																					  \
																						  \
		translate_jump_line(&asm_byte_code, second_lyr, cmd_num, &lm);					  \
	}																					
//-----------------------------------------------------------------------------------------

	while (true)
	{

		cur_asm_line_num++;

		prepare_for_line_check_pars(&cur_line_for_strtok, &cur_line, 
									&first_lyr, &second_lyr, &last_lyr, 
									&buf_str_asm_line_for_strtok, &buf_str_asm_line,
									&buf_str_asm_line_for_strtok_size, &buf_str_asm_line_size,
									&fp);

		if (!first_lyr)
		{}
		else if (is_label(first_lyr) && !second_lyr)
		{}
#include "../code_gen/code_gen.c"

		if (next_file_parser(&fp) == NULL)
		{

			clear_file_parser(&fp);
			break;
		}
	}

#undef DEF_CMD

	dump_prol_stack(&asm_byte_code, bin_file_ptr);
	clear_prol_stack(&asm_byte_code);

	clear_label_map(&lm);

	free(buf_str_asm_line_for_strtok);
	free(buf_str_asm_line);
	free(buf_str_of_asm_file);
}

#endif //ASM
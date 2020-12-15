#ifndef ASM
#define ASM

#include <string.h>
#include <stdio.h>

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
	else if (!first_lyr)											 					  \
	{																					  \
																						  \
		str_declareted = true;															  \
	}																					  \
	else if (args_count == ONE_ARG && arg_type == REGISTER && 							  \
			 second_lyr && is_reg(second_lyr) &&       								      \
			 strequ(cmd_name, first_lyr) && 											  \
			 last_lyr == NULL)                        									  \
	{                                                                                     \
                                                                                          \
		cur_byte_bin_format += cmd_size;                                                  \
		str_declareted = true;			                                                  \
	}    																				  \
	else if (args_count == ONE_ARG && arg_type == RAM &&								  \
			 second_lyr && is_ram(second_lyr) && 										  \
			 strequ(cmd_name, first_lyr) && 											  \
			 last_lyr == NULL)															  \
	{																					  \
																						  \
		cur_byte_bin_format += cmd_size;												  \
		str_declareted = true;															  \
	}                       						            						  \
	else if (args_count == ONE_ARG && arg_type == DIGIT && 								  \
			 second_lyr && is_digit(second_lyr) &&        								  \
		     strequ(cmd_name, first_lyr) &&											      \
		     last_lyr == NULL)                        									  \
	{                                                                                     \
                                                                                          \
		cur_byte_bin_format += cmd_size;              									  \
		str_declareted = true;						                                      \
	}                                                                                     \
	else if (args_count == ONE_ARG && is_jump &&                                          \
			 second_lyr &&                                   							  \
		     strequ(cmd_name, first_lyr) && 											  \
		     last_lyr == NULL)             									              \
	{                                                                                     \
        																				  \
        add_jump_list(&jl, cur_line, second_lyr, cur_asm_line_num);                       \
		cur_byte_bin_format += cmd_size;                               					  \
		str_declareted = true;										                      \
	}                                                                                     \
	else if (args_count == ZERO_ARG && is_label(first_lyr) && 							  \
			 last_lyr == NULL && second_lyr == NULL)                  					  \
	{                                                                                     \
                                                                                          \
		insert_label_map(&lm, first_lyr, cur_byte_bin_format);                            \
		str_declareted = true;										           			  \
	}                                                                                     \
	else if (args_count == ZERO_ARG &&                                                    \
			 strequ(cmd_name, first_lyr) && 											  \
			 last_lyr == NULL && second_lyr == NULL)									  \
	{                                                                           		  \
                                                                                		  \
		cur_byte_bin_format += cmd_size;      											  \
		str_declareted = true;					                                      	  \
	}                                                                           		  \
if (false)																		          \
{}
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

	while (true)
	{

#define FILE_RUN                                                                 \
		cur_asm_line_num++;														 \
																				 \
		char *cur_line_for_strtok = strcopy(cur_file_parser(&fp), 				 \
								            &buf_str_asm_line_for_strtok, 	     \
								            &buf_str_asm_line_for_strtok_size);	 \
																				 \
		char *cur_line            = strcopy(cur_file_parser(&fp), 				 \
								            &buf_str_asm_line, 					 \
								            &buf_str_asm_line_size);			 \
																				 \
																				 \
		char *first_lyr  = strtok(cur_line_for_strtok, " \t"),					 \
			 *second_lyr = strtok(NULL,                " \t"),					 \
			 *last_lyr   = strtok(NULL,                " \t");					 \
			 																	 \
		if (first_lyr && first_lyr[0] == ';')									 \
			first_lyr = NULL;													 \
			 																	 \
		if (!first_lyr || (second_lyr && second_lyr[0] == ';'))					 \
			second_lyr = NULL;													 \
																				 \
		if (!second_lyr || (last_lyr && last_lyr[0] == ';'))					 \
			last_lyr = NULL;													 
//--------------------------------------------------------------------------------

		FILE_RUN

		bool str_declareted = false;

		if (false)
		{}
#include "../code_gen/code_gen.c"

		if (!str_declareted)
		{

			can_asm = false;													  	          
			printf("\nerror: incorrect line\nline number: %ld\n%s\n", 				          
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

		printf("\nCan`t asm file.\n");

		clear_label_map(&lm);

		free(buf_str_asm_line_for_strtok);
		free(buf_str_asm_line);
		free(buf_str_of_asm_file);
		return;		
	}

	fp = new_file_parser(buf_str_of_asm_file);

	prol_stack asm_byte_code = new_prol_stack(sizeof(char));

#define DEF_CMD(cmd_name, cmd_num, cmd_size, args_count, arg_type, is_jump, execute_code) \
	else if (!first_lyr)											 					  \
	{																					  \
																						  \
	}																					  \
	else if (args_count == ONE_ARG && arg_type == REGISTER && 							  \
			 second_lyr && is_reg(second_lyr) &&       								      \
			 strequ(cmd_name, first_lyr) && 											  \
			 last_lyr == NULL)                        									  \
	{                                                                                     \
        																				  \
        unsigned char temp_cmd_num = cmd_num;                                             \
		push_prol_stack(&asm_byte_code, &temp_cmd_num);    								  \
																						  \
		long long temp_reg_num = get_reg_num(second_lyr);                                 \
		push_n_prol_stack(&asm_byte_code, &temp_reg_num, sizeof(long long));	 		  \
	}                                                                                     \
	else if (args_count == ONE_ARG && arg_type == RAM &&								  \
			 second_lyr && is_ram(second_lyr) && 										  \
			 strequ(cmd_name, first_lyr) && 											  \
			 last_lyr == NULL)															  \
	{																					  \
																						  \
		unsigned char temp_cmd_num = cmd_num;											  \
		push_prol_stack(&asm_byte_code, &temp_cmd_num);									  \
																						  \
		long long temp_reg_num = get_ram_reg_num(second_lyr);							  \
		push_n_prol_stack(&asm_byte_code, &temp_reg_num, sizeof(long long));			  \
	}                       						            						  \
	else if (args_count == ONE_ARG && arg_type == DIGIT && 								  \
			 second_lyr && is_digit(second_lyr) &&        								  \
		     strequ(cmd_name, first_lyr) &&											      \
		     last_lyr == NULL)                        									  \
	{                                                                                     \
        																				  \
        unsigned char temp_cmd_num = cmd_num;											  \
        push_prol_stack(&asm_byte_code, &temp_cmd_num);								      \
                                                                                          \
		long long temp_digit = get_digit(second_lyr);									  \
		push_n_prol_stack(&asm_byte_code, &temp_digit, sizeof(long long));                \
	}                                                                                     \
	else if (args_count == ONE_ARG && is_jump &&                                          \
			 second_lyr &&                                   							  \
		     strequ(cmd_name, first_lyr) && 											  \
		     last_lyr == NULL)             									              \
	{                                                                                     \
        																				  \
        unsigned char temp_cmd_num = cmd_num;											  \
        push_prol_stack(&asm_byte_code, &temp_cmd_num);									  \
        																			      \
        long long temp_label_byte = get_num_byte_label_map(&lm, second_lyr);			  \
        push_n_prol_stack(&asm_byte_code, &temp_label_byte, sizeof(long long));           \
	}                                                                                     \
	else if (args_count == ZERO_ARG && is_label(first_lyr) && 							  \
			 last_lyr == NULL && second_lyr == NULL)                  					  \
	{                                                                                     \
                                                                                          \
	}                                                                                     \
	else if (args_count == ZERO_ARG &&                                                    \
			 strequ(cmd_name, first_lyr) && 											  \
			 last_lyr == NULL && second_lyr == NULL)									  \
	{                                                                           		  \
                                 														  \
        unsigned char temp_cmd_num = cmd_num;                                             \
		push_prol_stack(&asm_byte_code, &temp_cmd_num);      							  \
	}                                                                           		  \
if (false)																		          \
{}
//-----------------------------------------------------------------------------------------

	while (true)
	{

		FILE_RUN

		if (false)
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

	#undef FILE_RUN
}
#endif //ASM
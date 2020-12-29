#ifndef LISTING
#define LISTING

#include <assert.h>

/*
	Write info about command in console
*/
void write_cmd_info (char *cmd_name, int cmd_num, int args_count, int arg_type, int is_jump,
					 char *buf_byte_code, size_t cur_byte);

void listing (FILE *bin_file_ptr)
{

	assert(bin_file_ptr);

	size_t buf_byte_code_size = filesize(bin_file_ptr);
	char *buf_byte_code = (char*) calloc(buf_byte_code_size, sizeof(char));
	fread(buf_byte_code, sizeof(char), buf_byte_code_size, bin_file_ptr);

	printf("---------------LISTING---------------\n"
		   "BYTE\tCMD\tNUM\n");

	size_t cur_byte = 0;

	while (cur_byte < buf_byte_code_size)
	{

#define DEF_CMD(cmd_name, cmd_num, cmd_size, args_count, arg_type, is_jump, execute_code) \
		else if (cmd_num == *(buf_byte_code + cur_byte))								  \
		{																				  \
																						  \
			write_cmd_info(cmd_name, cmd_num, args_count, arg_type, is_jump,			  \
						   buf_byte_code, cur_byte);									  \
			cur_byte += cmd_size;														  \
		}															
//-----------------------------------------------------------------------------------------

	if (false)
	{}
#include "../code_gen/code_gen.c"
	}

#undef DEF_CMD

printf("-------------------------------------\n");

printf("SIZE:\t%ld\n", buf_byte_code_size);

	free(buf_byte_code);
}

void write_cmd_info (char *cmd_name, int cmd_num, int args_count, int arg_type, int is_jump,
					 char *buf_byte_code, size_t cur_byte)
{

	printf("%ld\t%s\t%d\t", cur_byte, cmd_name, cmd_num);

	if (arg_type == REGISTER || arg_type == RAM)
	{

#define REG(reg, reg_num) 															  			 \
		else if (reg_num == *(unsigned char*)(buf_byte_code + cur_byte + sizeof(unsigned char))) \
		{														  					  			 \
																					  			 \
			if (arg_type == REGISTER)												  			 \
				printf("%s\t", #reg);												  			 \
			else																	  			 \
				printf("[%s]\t", #reg);												  			 \
		}																			
//------------------------------------------------------------------------------------------------

		if (false)
		{}
#include "../code_gen/reg_gen.c"

#undef REG
	}
	else if (arg_type == LABEL)
	{

		printf("%lld\t", *(long long*)(buf_byte_code + cur_byte + sizeof(unsigned char)));
	}
	else if (arg_type == DIGIT)
	{

		double digit = ((double)(*(long long*)(buf_byte_code + cur_byte + sizeof(unsigned char)))) / DOUBLE_PART;
		printf("%.2lf\t", digit);
	}
	else
		printf("-\t");

	if (is_jump)
		printf("JUMP");
	printf("\n");
}

#endif //LISTING 
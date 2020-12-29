#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "funcs/strsize.c"
#include "asm/asm_file.c"
#include "disasm/disasm_byte_code.c"
#include "exec/exec_byte_code.c"
#include "listing/listing.c"

//foo.asm -> foo.bin
void asm_file_name_to_bin_file_name (char **ams_file_name);

//foo.bin -> foo.disasm
void bin_file_name_to_disasm_file_name (char **bin_file_name);

int main (int argc, char *argv[])
{

	assert(argc > 1);

	if (strcmp(argv[1], "asm") == 0)
	{

		assert(argc > 2);

		char *asm_file_name = argv[2];

		size_t asm_file_name_size = strsize(asm_file_name),
			   bin_file_name_size = asm_file_name_size; 


		char *bin_file_name = (char*) calloc(asm_file_name_size, 
											  sizeof(char)); 

		memcpy(bin_file_name, asm_file_name, 
			    sizeof(char) * bin_file_name_size);
		//In this moment, bin_file_name = asm_file_name

		asm_file_name_to_bin_file_name(&bin_file_name);

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

		assert(argc > 2);

		char *bin_file_name = argv[2];
		FILE *bin_file_ptr = fopen(bin_file_name, "rb");

		assert(bin_file_ptr);

		exec_byte_code(bin_file_ptr);

		fclose(bin_file_ptr);
	}
	else if (strcmp(argv[1], "disasm") == 0)
	{

		assert(argc > 2);

		char *bin_file_name = argv[2];

		size_t bin_file_name_size = strsize(bin_file_name),
			   disasm_file_name_size = bin_file_name_size; 


		char *disasm_file_name = (char*) calloc(disasm_file_name_size, 
											    sizeof(char)); 

		memcpy(disasm_file_name, bin_file_name, 
			    sizeof(char) * disasm_file_name_size);
		//In this moment, disasm_file_name = bin_file_name

		bin_file_name_to_disasm_file_name(&disasm_file_name);

		FILE *bin_file_ptr = fopen(bin_file_name, "rb"),
			 *disasm_file_ptr = fopen(disasm_file_name, "w");

		assert(bin_file_ptr && disasm_file_ptr);

		disasm_byte_code(bin_file_ptr, disasm_file_ptr);

		free(disasm_file_name);

		fclose(bin_file_ptr);
		fclose(disasm_file_ptr);
	}
	else if (strcmp(argv[1], "listing") == 0)
	{

		assert(argc > 2);

		char *bin_file_name = argv[2];
		FILE *bin_file_ptr = fopen(bin_file_name, "rb");

		assert(bin_file_ptr);

		listing(bin_file_ptr);

		fclose(bin_file_ptr);
	}
	else
		printf("TALANT_ERROR_ARGUMENT\n");

	return 0;
}

void asm_file_name_to_bin_file_name (char **asm_file_name)
{


	size_t asm_file_name_size = strsize(*asm_file_name),
		   bin_file_name_size = asm_file_name_size;

	int dot_poz = -1;

	for (int i = asm_file_name_size - 1; i >= 0; --i)
		if ((*asm_file_name)[i] == '.')
		{

			dot_poz = i;
			break;
		}

	if (dot_poz == -1)
	{

		*asm_file_name = realloc(*asm_file_name, bin_file_name_size + 5);

		(*asm_file_name)[bin_file_name_size] = '.';
		(*asm_file_name)[bin_file_name_size + 1] = 'b';
		(*asm_file_name)[bin_file_name_size + 2] = 'i';
		(*asm_file_name)[bin_file_name_size + 3] = 'n';
		(*asm_file_name)[bin_file_name_size + 4] = '\0';

		return;
	}	

	if (dot_poz + 4 >= bin_file_name_size)
		*asm_file_name = realloc(*asm_file_name, dot_poz + 5);

	(*asm_file_name)[dot_poz + 1] = 'b';
	(*asm_file_name)[dot_poz + 2] = 'i';
	(*asm_file_name)[dot_poz + 3] = 'n';
	(*asm_file_name)[dot_poz + 4] = '\0';
}

void bin_file_name_to_disasm_file_name (char **bin_file_name)
{

	size_t bin_file_name_size = strsize(*bin_file_name),
		   disasm_file_name_size = bin_file_name_size;

	int dot_poz = -1;

	for (int i = bin_file_name_size - 1; i >= 0; --i)
		if ((*bin_file_name)[i] == '.')
		{

			dot_poz = i;
			break;
		}

	if (dot_poz == -1)
	{

		*bin_file_name = realloc(*bin_file_name, disasm_file_name_size + 8);

		(*bin_file_name)[disasm_file_name_size] = '.';
		(*bin_file_name)[disasm_file_name_size + 1] = 'd';
		(*bin_file_name)[disasm_file_name_size + 2] = 'i';
		(*bin_file_name)[disasm_file_name_size + 3] = 's';
		(*bin_file_name)[disasm_file_name_size + 4] = 'a';
		(*bin_file_name)[disasm_file_name_size + 5] = 's';
		(*bin_file_name)[disasm_file_name_size + 6] = 'm';
		(*bin_file_name)[disasm_file_name_size + 7] = '\0';

		return;
	}	

	if (dot_poz + 7 >= disasm_file_name_size)
		*bin_file_name = realloc(*bin_file_name, dot_poz + 8);

	(*bin_file_name)[dot_poz + 1] = 'd';
	(*bin_file_name)[dot_poz + 2] = 'i';
	(*bin_file_name)[dot_poz + 3] = 's';
	(*bin_file_name)[dot_poz + 4] = 'a';
	(*bin_file_name)[dot_poz + 5] = 's';
	(*bin_file_name)[dot_poz + 6] = 'm';
	(*bin_file_name)[dot_poz + 7] = '\0';	
}


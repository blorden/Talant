#ifndef JUMP_LIST
#define JUMP_LIST

#include <assert.h>

#include "prol_stack.c"
#include "label_map.c"
#include "../funcs/strsize.c"

typedef struct __jump_list
{

	prol_stack lines,
			   labels,
			   line_nums;

	size_t size;

} jump_list;

jump_list new_jump_list ()
{

	jump_list temp;
	temp.lines     = new_prol_stack(sizeof(char));
	temp.labels    = new_prol_stack(sizeof(char));
	temp.line_nums = new_prol_stack(sizeof(size_t));

	temp.size = 0;

	return temp;
}

//add label and info 
void add_jump_list (jump_list *jl, 
						const char* line, 
						const char* label, 
						const size_t line_num)
{

	assert(jl && line && label);

	push_n_prol_stack(&jl->lines,  line, strsize(line));
	push_n_prol_stack(&jl->labels, label, strsize(label));
	push_prol_stack(&jl->line_nums, &line_num);

	jl->size++;
}

void clear_jump_list (jump_list *jl)
{

	assert(jl);

	clear_prol_stack(&jl->lines);
	clear_prol_stack(&jl->labels);
	clear_prol_stack(&jl->line_nums);

	jl->size = 0;
}

//check: exist label in list or not
void check_jump_list (jump_list *jl, label_map *jm, bool *can_asm)
{

	assert(jl && jm);

	size_t label_iterator = 0,
		   line_iterator = 0;

	for (int i = 0; i < jl->size; ++i)
	{

		if (!exist_label_map(jm, (char*)get_prol_stack(&jl->labels, label_iterator)))
		{

			*can_asm = false;
			printf("\nerror: label is not exist\n"
				   "line num: %ld\n"
				   "%s\n", *(size_t*)get_prol_stack(&jl->line_nums, i),
				   		   (char*)get_prol_stack(&jl->lines, line_iterator));
		}

		label_iterator += strsize((char*)get_prol_stack(&jl->labels, label_iterator));
		line_iterator  += strsize((char*)get_prol_stack(&jl->lines, line_iterator));
	}
}

#endif //JUMP_LIST
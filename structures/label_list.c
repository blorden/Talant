#ifndef LABEL_LIST
#define LABEL_LIST

#include "prol_stack.c"

#include <assert.h>

typedef struct __label_list
{

	prol_stack label_nums,
			   bytes;
} label_list;

label_list new_label_list ()
{

	label_list temp;

	temp.label_nums = new_prol_stack(sizeof(long long));
	temp.bytes = new_prol_stack(sizeof(long long));

	return temp;
}

void insert_label_list (label_list *ll, long long label_num, long long byte)
{

	assert(ll);

	push_prol_stack(&ll->label_nums, &label_num);
	push_prol_stack(&ll->bytes, &byte);
}

//get label num in byte
long long get_label_list (label_list *ll, long long byte)
{

	assert(ll);

	int l = 0, r = ll->label_nums.size;

	//bin search to find need label
	while (r - l > 1)
	{

		int mid = (l + r) / 2;

		if (*(long long*)get_prol_stack(&ll->bytes, mid) <= byte)
			l = mid;
		else
			r = mid;
	}

	return *(long long*)get_prol_stack(&ll->label_nums, l);
}

void clear_label_list (label_list *ll)
{

	assert(ll);

	clear_prol_stack(&ll->label_nums);
	clear_prol_stack(&ll->bytes);
}

#endif //LABEL_LIST
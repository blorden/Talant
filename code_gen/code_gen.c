#define DOUBLE_PART 100

DEF_CMD("in", IN_CMD, ZERO_ARG_SIZE, ZERO_ARG, VOID_ARG, NOT_JUMP,
{

	double input_digit = 0;
	scanf("%lf", &input_digit);

	long long stack_digit = (long long)(input_digit * DOUBLE_PART);
	push_n_prol_stack(&exec_stack, &stack_digit, sizeof(long long));
})

DEF_CMD("out", OUT_CMD, ZERO_ARG_SIZE, ZERO_ARG, VOID_ARG, NOT_JUMP,
{

	long long stack_digit = *(long long*)get_prol_stack(&exec_stack, 
   													    exec_stack.size - sizeof(long long));

	long long stack_digit_mod = llabs(stack_digit) % DOUBLE_PART;

	if (stack_digit / DOUBLE_PART == 0 && stack_digit < 0 && stack_digit_mod > 0)
		printf("-");

	stack_digit /= DOUBLE_PART;

	printf("%lld", stack_digit);

	if (stack_digit_mod > 0)
		printf(".%lld", stack_digit_mod);

	printf("\n");
	fflush(stdout);
})

DEF_CMD("sqrt", SQRT_CMD, ZERO_ARG_SIZE, ZERO_ARG, VOID_ARG, NOT_JUMP,
{

	long long stack_digit = *(long long*)get_prol_stack(&exec_stack, 
   													    exec_stack.size - sizeof(long long));

	double digit_sqrt = sqrt(((double)stack_digit) / DOUBLE_PART);
	stack_digit = (long long)(digit_sqrt * DOUBLE_PART);

	push_n_prol_stack(&exec_stack, &stack_digit, sizeof(long long));
})

DEF_CMD("mul", MUL_CMD, ZERO_ARG_SIZE, ZERO_ARG, VOID_ARG, NOT_JUMP,
{

	long long first_digit  = *(long long*)get_prol_stack(&exec_stack, 
   									    				 exec_stack.size - sizeof(long long));
	long long second_digit = *(long long*)get_prol_stack(&exec_stack, 
   													     exec_stack.size - 2*sizeof(long long));

	long long stack_digit = first_digit * second_digit;
	stack_digit /= DOUBLE_PART;

	push_n_prol_stack(&exec_stack, &stack_digit, sizeof(long long));
})

DEF_CMD("div", DIV_CMD, ZERO_ARG_SIZE, ZERO_ARG, VOID_ARG, NOT_JUMP,
{

	long long first_digit  = *(long long*)get_prol_stack(&exec_stack, 
   									    				 exec_stack.size - sizeof(long long));
	long long second_digit = *(long long*)get_prol_stack(&exec_stack, 
   													     exec_stack.size - 2*sizeof(long long));

   	double temp_double_digit = ((double)second_digit) / DOUBLE_PART;
   	temp_double_digit /= ((double)first_digit) / DOUBLE_PART;

   	long long stack_digit = temp_double_digit * DOUBLE_PART;

   	push_n_prol_stack(&exec_stack, &stack_digit, sizeof(long long));
})

DEF_CMD("add", ADD_CMD, ZERO_ARG_SIZE, ZERO_ARG, VOID_ARG, NOT_JUMP,
{

	long long first_digit  = *(long long*)get_prol_stack(&exec_stack, 
   									    				 exec_stack.size - sizeof(long long));
	long long second_digit = *(long long*)get_prol_stack(&exec_stack, 
   													     exec_stack.size - 2*sizeof(long long));

	double temp_double_digit = ((double)second_digit) / DOUBLE_PART;
   	temp_double_digit += ((double)first_digit) / DOUBLE_PART;

   	long long stack_digit = temp_double_digit * DOUBLE_PART;

   	push_n_prol_stack(&exec_stack, &stack_digit, sizeof(long long));
})

DEF_CMD("sub", SUB_CMD, ZERO_ARG_SIZE, ZERO_ARG, VOID_ARG, NOT_JUMP,
{

	long long first_digit  = *(long long*)get_prol_stack(&exec_stack, 
   									    				 exec_stack.size - sizeof(long long));
	long long second_digit = *(long long*)get_prol_stack(&exec_stack, 
   													     exec_stack.size - 2*sizeof(long long));

	double temp_double_digit = ((double)second_digit) / DOUBLE_PART;
   	temp_double_digit -= ((double)first_digit) / DOUBLE_PART;

   	long long stack_digit = temp_double_digit * DOUBLE_PART;

   	push_n_prol_stack(&exec_stack, &stack_digit, sizeof(long long));
})

DEF_CMD("mod", MOD_CMD, ZERO_ARG_SIZE, ZERO_ARG, VOID_ARG, NOT_JUMP,
{

	long long first_digit  = *(long long*)get_prol_stack(&exec_stack, 
   									    				 exec_stack.size - sizeof(long long));
	long long second_digit = *(long long*)get_prol_stack(&exec_stack, 
   													     exec_stack.size - 2*sizeof(long long));

	double temp_double_digit = ((double)second_digit) / DOUBLE_PART;
   	temp_double_digit = fmodl(temp_double_digit, ((double)first_digit) / DOUBLE_PART);

   	long long stack_digit = temp_double_digit * DOUBLE_PART;

   	push_n_prol_stack(&exec_stack, &stack_digit, sizeof(long long));
})

DEF_CMD("push", PUSH_REG_CMD, ONE_ARG_SIZE, ONE_ARG, REGISTER, NOT_JUMP,
{

	long long push_reg_num =  *(long long*)(buf_byte_code + cur_byte + 1);

	push_n_prol_stack(&exec_stack, &regs[push_reg_num], sizeof(long long)); 
})

DEF_CMD("push", PUSH_DIG_CMD, ONE_ARG_SIZE, ONE_ARG, DIGIT, NOT_JUMP,
{

	long long push_digit  =  *(long long*)(buf_byte_code + cur_byte + 1);

	push_n_prol_stack(&exec_stack, &push_digit, sizeof(long long));
})

DEF_CMD("pop", POP_CMD, ONE_ARG_SIZE, ONE_ARG, REGISTER, NOT_JUMP,
{

	long long pop_digit  = *(long long*)get_prol_stack(&exec_stack,
													   exec_stack.size - sizeof(long long));

	pop_n_prol_stack(&exec_stack, sizeof(long long));

	long long reg_num    =  *(long long*)(buf_byte_code + cur_byte + 1);

	regs[reg_num] = pop_digit;	
})

DEF_CMD("jmp", JMP_CMD, ONE_ARG_SIZE, ONE_ARG, LABEL, JUMP,
{

	long long jump_byte =  *(long long*)(buf_byte_code + cur_byte + 1);

	cur_byte = jump_byte;
})

DEF_CMD("jb", JB_CMD, ONE_ARG_SIZE, ONE_ARG, LABEL, JUMP,
{

	long long jump_byte =  *(long long*)(buf_byte_code + cur_byte + 1);

	if (cmp_res < 0)
		cur_byte = jump_byte;
	else
		cur_byte += ONE_ARG_SIZE;
})

DEF_CMD("jbe", JBE_CMD, ONE_ARG_SIZE, ONE_ARG, LABEL, JUMP,
{

	long long jump_byte =  *(long long*)(buf_byte_code + cur_byte + 1);

	if (cmp_res < 0 || cmp_res == 0)
		cur_byte = jump_byte;
	else
		cur_byte += ONE_ARG_SIZE;	
})

DEF_CMD("je", JE_CMD, ONE_ARG_SIZE, ONE_ARG, LABEL, JUMP,
{

	long long jump_byte =  *(long long*)(buf_byte_code + cur_byte + 1);

	if (cmp_res == 0)
		cur_byte = jump_byte;
	else
		cur_byte += ONE_ARG_SIZE;
})

DEF_CMD("jne", JNE_CMD, ONE_ARG_SIZE, ONE_ARG, LABEL, JUMP,
{

	long long jump_byte =  *(long long*)(buf_byte_code + cur_byte + 1);

	if (cmp_res != 0)
		cur_byte = jump_byte;
	else
		cur_byte += ONE_ARG_SIZE;
})

DEF_CMD("ja", JA_CMD, ONE_ARG_SIZE, ONE_ARG, LABEL, JUMP,
{

	long long jump_byte = *(long long*)(buf_byte_code + cur_byte + 1);

	if (cmp_res > 0)
		cur_byte = jump_byte;
	else
		cur_byte += ONE_ARG_SIZE;
})

DEF_CMD("jae", JAE_CMD, ONE_ARG_SIZE, ONE_ARG, LABEL, JUMP,
{

	long long jump_byte = *(long long*)(buf_byte_code + cur_byte + 1);

	if (cmp_res > 0 || cmp_res == 0)
		cur_byte = jump_byte;
	else
		cur_byte += ONE_ARG_SIZE;
})

DEF_CMD("jm", JM_CMD, ONE_ARG_SIZE, ONE_ARG, LABEL, JUMP,
{

	long long jump_byte = *(long long*)(buf_byte_code + cur_byte + 1);

	time_t bad_time = 0;
	time(&bad_time);
	char *time = asctime(localtime(&bad_time));
	time[3] = '\0';

	if (strequ(time, "Mon"))
		cur_byte = jump_byte;
	else
		cur_byte += ONE_ARG_SIZE;
})

DEF_CMD("call", CALL_CMD, ONE_ARG_SIZE, ONE_ARG, LABEL, JUMP,
{

	long long jump_byte = *(long long*)(buf_byte_code + cur_byte + 1);
	long long ret_byte = cur_byte + ONE_ARG_SIZE;

	push_prol_stack(&ret_stack, &ret_byte);

	cur_byte = jump_byte;
})

DEF_CMD("ret", RET_CMD, ZERO_ARG_SIZE, ZERO_ARG, VOID_ARG, JUMP,
{

	long long ret_byte	 = *(long long*)get_prol_stack(&ret_stack, ret_stack.size - 1);

	cur_byte = ret_byte;

	pop_prol_stack(&ret_stack);
})

DEF_CMD("hlt", HLT_CMD, ZERO_ARG_SIZE, ZERO_ARG, VOID_ARG, JUMP,
{

	cur_byte = buf_byte_code_size;
})

DEF_CMD("cmp", CMP_CMD, ZERO_ARG_SIZE, ZERO_ARG, VOID_ARG, NOT_JUMP,
{

	long long first_digit  = *(long long*)get_prol_stack(&exec_stack, 
   									    				 exec_stack.size - sizeof(long long));
	long long second_digit = *(long long*)get_prol_stack(&exec_stack, 
   													     exec_stack.size - 2*sizeof(long long));

	cmp_res = second_digit - first_digit;
})

DEF_CMD("push", PUSH_RAM_CMD, ONE_ARG_SIZE, ONE_ARG, RAM, NOT_JUMP, 
{

	long long ram_num = regs[*(long long*)(buf_byte_code + cur_byte + 1)];

	push_n_prol_stack(&exec_stack, &ram[ram_num], sizeof(long long));
})

DEF_CMD("pop", POP_RAM_CMD, ONE_ARG_SIZE, ONE_ARG, RAM, NOT_JUMP,
{

	long long ram_num  = regs[*(long long*)(buf_byte_code + cur_byte + 1)];

	if (ram_num <= ram_sz)
	{

		ram_sz = 2*ram_num + 100;
		ram = realloc(ram, sizeof(long long) * ram_sz);
	}

	ram[ram_num] = *(long long*)get_prol_stack(&exec_stack, 
												exec_stack.size - sizeof(long long));

	pop_n_prol_stack(&exec_stack, sizeof(long long));
})
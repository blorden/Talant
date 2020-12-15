#ifndef CMD_ENUM
#define CMD_ENUM

enum commands_nums
{

	IN_CMD,
	OUT_CMD, 
	SQRT_CMD, 
	MUL_CMD, 
	DIV_CMD,
	ADD_CMD,
	SUB_CMD,
	MOD_CMD,
	PUSH_REG_CMD,
	PUSH_DIG_CMD,
	POP_CMD,
	JMP_CMD,
	JB_CMD,
	JBE_CMD,
	JE_CMD,
	JNE_CMD,
	JA_CMD,
	JAE_CMD,
	JM_CMD,
	CALL_CMD,
	RET_CMD,
	HLT_CMD,
	CMP_CMD,
	PUSH_RAM_CMD,
	POP_RAM_CMD
};

enum commands_arg_count
{

	ZERO_ARG,
	ONE_ARG
};

enum commads_jump_info
{

	NOT_JUMP,
	JUMP
};

enum commands_type
{

	VOID_ARG,
	DIGIT,
	REGISTER,
	LABEL,
	RAM
};

enum commands_size
{

	VOID_OR_COMMENT_SIZE,
	ZERO_ARG_SIZE = 1,
	ONE_ARG_SIZE = 9
};

#endif //CMD_ENUM
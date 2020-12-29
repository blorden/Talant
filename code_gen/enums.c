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
	RAM,
	RAM_NUM,
	REGISTER_NUM,
	CMP_RES
};

enum helper_enum
{

	DOUBLE_PART = 100,
	MAX_DIGIT_LENGTH = 14
};

enum segfalt_destroer
{

	SIZE_MULTIPLY = 2,
	CONSTANT_ADD_SIZE = 30
};

enum maximums
{

	MAX_REGS_COUNT = 256,
	MAX_DSL_ARGS = 10
};

enum commands_size
{

	VOID_OR_COMMENT_SIZE,
	ZERO_ARG_SIZE = 1,
	ONE_ARG_REG_OR_RAM_SIZE = 2,
	ONE_ARG_DIGIT_OR_LABEL_SIZE = 9
};

#endif //CMD_ENUM
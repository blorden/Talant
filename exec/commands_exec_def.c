#ifndef COMMANDS_EXEC_DEF
#define COMMANDS_EXEC_DEF

//read value and write him to bin_file_args
#define IN(arg_num)                                                   \
   scanf("%lf", &double_digit);                                       \
                                                                      \
   bin_file_args[arg_num] = (long long)(double_digit * DOUBLE_PART); 
//-------------------------------------------------------------------

//push in exec stack value in bin_file_args
#define PUSH(arg_num)                                                          \
   push_n_prol_stack(&exec_stack, &bin_file_args[arg_num], sizeof(long long));
//-----------------------------------------------------------------------------------

//get exec_stack_arg_num back value form exec_stack
#define GET(arg_num, exec_stack_arg_num)                                                                 \
   bin_file_args[arg_num] = *(long long*)get_prol_stack(&exec_stack,                                     \
                                              exec_stack.size - exec_stack_arg_num * sizeof(long long)); 
//-------------------------------------------------------------------------------------------------------------------

//printf value in bin from bin_file_args
#define OUT(arg_num)                                                        \
   if (abs(fmod(bin_file_args[arg_num], DOUBLE_PART)) < 1.0 / DOUBLE_PART)  \
      printf("%lld\n", bin_file_args[arg_num] / DOUBLE_PART);               \
   else                                                                     \
      printf("%.2lf\n", ((double)bin_file_args[arg_num]) / DOUBLE_PART);    \
   fflush(stdout);
//----------------------------------------------------------------------------

//take sqrt from value
#define SQRT(arg_num)                                                     \
   double_digit = sqrt(((double)bin_file_args[arg_num]) / DOUBLE_PART);   \
   bin_file_args[arg_num] = (long long)(double_digit) * DOUBLE_PART;           
//--------------------------------------------------------------------------

//muliply values in bin_file_args
#define MUL(first_arg_num, second_arg_num)                            \
      bin_file_args[first_arg_num] *= bin_file_args[second_arg_num];  \
      bin_file_args[first_arg_num] /= DOUBLE_PART;
//--------------------------------------------------------------------------

//division to values
#define DIV(first_arg_num, second_arg_num)                                   \
      double_digit = ((double)bin_file_args[first_arg_num]) / DOUBLE_PART;   \
      double_digit /= ((double)bin_file_args[second_arg_num]) / DOUBLE_PART; \
                                                                             \
      bin_file_args[first_arg_num] = double_digit * DOUBLE_PART;
//---------------------------------------------------------------------------

//sum of values
#define ADD(first_arg_num, second_arg_num)                     \
      double_digit = ((double)bin_file_args[first_arg_num]);   \
      double_digit += ((double)bin_file_args[second_arg_num]); \
                                                               \
      bin_file_args[first_arg_num] = double_digit;
//---------------------------------------------------------------------------

//difference
#define SUB(first_arg_num, second_arg_num)                     \
      double_digit = ((double)bin_file_args[first_arg_num]);   \
      double_digit -= ((double)bin_file_args[second_arg_num]); \
                                                               \
      bin_file_args[first_arg_num] = double_digit;
//---------------------------------------------------------------------------

//take values form bin file
#define TAKE(arg_num, file_arg_type)                                                                          \
      if (file_arg_type == REGISTER)                                                                          \
         bin_file_args[arg_num] = regs[*(unsigned char*)(buf_byte_code + cur_byte + sizeof(unsigned char))];  \
      else if (file_arg_type == DIGIT)                                                                        \
         bin_file_args[arg_num] = *(long long*)(buf_byte_code + cur_byte + sizeof(unsigned char));            \
      else if (file_arg_type == RAM)                                                                          \
      {                                                                                                       \
                                                                                                              \
         ram_num = regs[*(unsigned char*)(buf_byte_code + cur_byte + sizeof(unsigned char))];                 \
         bin_file_args[arg_num] = ram[ram_num];                                                               \
      }                                                                                                       \
      else if (file_arg_type == RAM_NUM)                                                                      \
         bin_file_args[arg_num] = regs[*(unsigned char*)(buf_byte_code + cur_byte + sizeof(unsigned char))];  \
      else if (file_arg_type == REGISTER_NUM)                                                                 \
         bin_file_args[arg_num] = *(unsigned char*)(buf_byte_code + cur_byte + sizeof(unsigned char));
//-------------------------------------------------------------------------------------------------------------

//set values 
#define SET(first_arg_num, second_arg_num, set_arg_type)                        \
      if (set_arg_type == REGISTER)                                             \
         regs[bin_file_args[first_arg_num]] = bin_file_args[second_arg_num];    \
      else if (set_arg_type == RAM)                                             \
      {                                                                         \
                                                                                \
         ram_num = bin_file_args[first_arg_num];                                \
         if (ram_num <= ram_sz)                                                 \
         {                                                                      \
                                                                                \
            ram_sz = SIZE_MULTIPLY*ram_num + CONSTANT_ADD_SIZE;                 \
            ram = realloc(ram, sizeof(long long) * ram_sz);                     \
         }                                                                      \
                                                                                \
         ram[ram_num] = bin_file_args[second_arg_num];                          \
      }                                                                         \
      else if (set_arg_type == CMP_RES)                                         \
         cmp_res = bin_file_args[first_arg_num] - bin_file_args[second_arg_num];                               
//------------------------------------------------------------------------------

//jump to byte if condition true
#define JMPC(condition)                                                               \
      if (cmp_res condition 0)                                                        \
         cur_byte = *(long long*)(buf_byte_code + cur_byte + sizeof(unsigned char));  \
      else                                                                            \
         cur_byte += ONE_ARG_DIGIT_OR_LABEL_SIZE;
//-------------------------------------------------------------------------------------

//return byte call created
#define JMPR cur_byte = *(long long*)get_prol_stack(&ret_stack, ret_stack.size - 1);

//pop from ret_stack
#define POPR pop_prol_stack(&ret_stack);

//push value to ret_stack
#define PUSHR                                             \
      ret_byte = cur_byte + ONE_ARG_DIGIT_OR_LABEL_SIZE;  \
      push_prol_stack(&ret_stack, &ret_byte);
//-------------------------------------------------------

//jump to byte
#define JMP cur_byte = *(long long*)(buf_byte_code + cur_byte + sizeof(unsigned char));

//getval from bin_file_args
#define GETVAL(arg_num) bin_file_args[arg_num]

//pop value from exec_stack
#define POP pop_n_prol_stack(&exec_stack, sizeof(long long));

//stop execute program
#define HLT cur_byte = buf_byte_code_size;

#endif //COMMANDS_EXEC_DEF
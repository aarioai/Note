#  AS (Assembler Language)

###################################  1_begin.s  #################################################
.section .data

# start
.section .text

.globl _start

data_items:
  .long 4,2,200,31,45,67,3,65,27,48,94,74,2,40,9999999
  
_start:

# Register  // first char: r is for 64-bit, e.g. rax;   eax is for 32-bit;   ax is for 16-bit
#   General Register
#     %rax
#     %rbx
#     %rcx
#     %rdx
#     %rdi  // 64-bit index register, range from [0,]
#     %rsi
#   Special Register
#     %rbp
#     %rsp
#     %rip
#     %rflags  
#-------------------------------------------------------------------------------
# %eax   command    %ebx              %ecx    %edx
#   1      exit     int error code
#   45     brk      break 
#   54     ioctl    int fd           request   parameters 
#-------------------------------------------------------------------------------
# movl source destination
#   寻址方式
#     立即寻址  $VALUE, REGISTER   // movl $1, %eax==>*(%eax) = 1
#     寄存器寻址
#     直接寻址  ADDR, REGISTER  // movl 1, %eax     ==> *(%eax) = 1
#                                  movl %eax, %ebx  ==> *(%ebx) = %eax
#     变址寻址
#     间接寻址  (REGISTER_A) REGISTER_B // movl (%eax) %ebx ===> %ebx = %eax
#     基址寻址  LEN(ADDR_START), REGISTER // movl 4(%eax), %ebx ==> %ebx = (void *)%eax + 4
#     索引寻址  ADDR_START(,INDEX_REGISTER, LENGTH) 
#              // movl ADDR_START(, %edi, 4), %eax  ==> %eax = (int *)ADDR_START + %edi
movl $0, %edi    # assign edi index to 0
movl data_items(,%edi, 4), %eax   # load first long to %eax
movl %eax, %ebx

start_loop:

# cmpl 
#   je jg jge jl jle jmp(just jump without comparing)
cmpl $9999999 %eax
je loop_exit
incl %edi
movl data_items(,%edi,4), %eax
cmpl %ebx, %eax
jle start_loop
movl %eax, %ebx
jmp start_loop

loop_exit:

movl $1, %eax      # move 1 to register %eax, do command exit()

# int $hex_interrupt_number            // interrupt
int $0x80
##########################################################################################

# sh$ as 1_begin.s -o 1.o
# sh$ ld 1.o -o 1
# sh$ ./1
# sh$ echo $? // get the error code of program in Linux 


###################################  2_func.s  #################################################
.section .data

# start
.section .text

.globl _start

# .globl factorial

_start:

int $0x80
##########################################################################################
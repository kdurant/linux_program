# gcc -no-pie cpuid.s
.section    .data
output:
    .ascii "The process Vendor ID is 'xxxxxxxxxxxxxxxx'\n"

.section    .text
.globl	main
main:
# clear EAX， EAX的值决定cpuid输出的内容
    movl    $0x00,     %eax
    cpuid

# ebx, edx, ecx, cpuid的输出被放到这三个寄存器中
    movl    $output, %edi 
    movl    %ebx,   28(%edi)
    movl    %edx,   32(%edi)
    movl    %ecx,   36(%edi)

# 标准系统调用过程
    movl    $4,     %eax
    movl    $1,     %ebx
    movl    $output,%ecx
    movl    $44,    %edx
    int     $0x80

    movl    $1,     %eax
    movl    $0,     %ebx
    int     $0x80


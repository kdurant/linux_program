# gcc -no-pie -m32 c_io1.s
.section .data
msg:
    .asciz  "Hello,world.\n"

.section    .text
.globl	main
main:
    pushl   $msg
    call    printf
    popl    %eax

    pushl   $0
    call    exit

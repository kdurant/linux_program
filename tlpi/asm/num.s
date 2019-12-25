.section    .data
msg:
    .asciz "The value is:0x%x.\n"
int8:
    .byte   0xda
int16:
    .short  0xabcd
int32:
    .int    0x12345678

.section    .text
.globl	main
main:
#movl    $0      %eax
    movb    int8,   %al
    pushl   %eax
    pushl   $msg
    call printf
    addl    $8,     %esp

    pushw   $0
    pushw   int16
    pushl   $msg
    call    printf
    addl    $8,     %esp

    pushl   $0
    call exit

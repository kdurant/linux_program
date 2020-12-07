# [语法格式](https://blog.csdn.net/zhaofuguang/article/details/18213507)
- Intel
- AT&T
为了区分格式，我们将Intel格式的汇编代码文件后缀名写为.asm，而AT&T的写为.s
 
# 编译器

1. nasm 
    使用的是 Intel 汇编语法
    ```bash 
    nasm -f elf64 -g -F dwarf source.asm
    ld source.o -o a.out
    ```

2. masm

3. gas 
    使用标准的 AT&T 汇编语法, 默认使用`_start`作为入口。
    但可用在ld时重新指定入口函数
    ```bash 
    as source.s -o objfile.o
    ld objfile.o -o execode

    ld objfile.o -o execode --entry=main
    ```
4. gcc
    使用`main`作为入口.
    扩展名最好是大写的`S`。这是因为，大写的 S 可以使 gcc 自动识别汇编程序中的 C 预处理命令，像#include、#define、#ifdef、 #endif 等，也就是说，使用 gcc 进行编译，你可以在 汇编程序中使用 C 的预处理命令。

| 功能       | nasm                | att                  | masm        |
|------------|---------------------|----------------------|-------------|
| 数据段     | secton .data        | .section .data       | .data       |
| bbs段      | secton .bss         | .section .bss        | .bss        |
| 文本段     | secton .text        | .section .text       | .code       |
| 定义变量   | var db 0x12         | var: .int 0x12       | var DWORD 0 |
| 字符串长度 | strLen equ $-str1-1 | strLen: .int .str1-1 |             |

# 函数调用约定

# 中断说明
## 0x80
    通过int 0x80，就可使用内核资源

## syscall
    syscall 是x86_64架构中专门做系统调用的指令

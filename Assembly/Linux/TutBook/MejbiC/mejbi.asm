extern printf
global main

section .data
    fmt db "Hello world! %s %s", 10, 0
    msg db "XD", 0
section .text
main:
    push rbp
    mov rbp, rsp

    mov rdi, fmt
    mov rsi, 0
    mov rax, 0
    call printf

    leave ; delet stack frame
    ret
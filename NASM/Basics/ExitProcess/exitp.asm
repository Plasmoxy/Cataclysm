global _main
extern _printf

section .data
t: db "Hello", 10

section .text
_main:
    push ebp
    mov ebp, esp

    push t
    call _printf
    add esp, 8

    leave
    mov eax, 0 ; exit 0
ret
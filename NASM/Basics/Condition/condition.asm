global _main
extern _printf


section .data
    numf: db "%d", 10, 0

section .text
_main:
    push ebp
    mov ebp, esp

    mov eax, 4
    mov ebx, 2

    cmp eax, ebx
    jne .else
        push 1
        push numf
        call _printf
    jmp .fi
    .else:
        push 0
        push numf
        call _printf
    .fi:
    

    mov esp, ebp

    leave
    mov eax, 0
ret

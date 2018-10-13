; x86 NASM

extern _printf

global _main

section .data
    numf: db "->%d", 10, 0
    a: dd 7

section .bss
    fourBytes: resb 4

section .text
_main:
    push ebp
    mov ebp, esp
    
    call showChange
    call printLocalVariable

    leave
    mov eax, 0
ret


showChange:
    push ebp
    mov ebp, esp

    push dword [a]
    push numf
    call _printf
    mov esp, ebp

    mov dword [a], 4

    push dword [a]
    push numf
    call _printf
    mov esp, ebp

    leave
ret


printLocalVariable:
    push ebp
    mov ebp, esp

    mov dword[ebp-4], 7 ; -> a

    add dword[ebp-4], 1
    
    push dword[ebp-4]
    push numf
    call _printf
    

    leave
ret
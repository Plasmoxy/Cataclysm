section .data
    a dd 0
    b dd 0
section .text
    global _start
_start:
    mov dword [a], 4
    mov dword [b], 5

    ; mov pointer of a to eax
    mov dword eax, a

    ; change a by eax pointer
    mov dword [eax], 80

    

    mov rax, 60
    mov rdi, 0
    syscall
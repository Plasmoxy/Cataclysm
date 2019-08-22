section .data
    a ddq 0x1A000000000000000
    b ddq 0x2C000000000000000
    sum ddq 0
section .text
    global _start
_start:
    ; store a in rax and rbx
    mov rax, qword [a]
    mov rbx, qword [a+8]

    ; add LS of b to rax, carry is stored in rFlags
    add rax, qword [b]
    
    ; add MS of b to rdx, use carry
    adc rbx, qword [b+8]

    ; store result from rax and rbx into result sum
    mov qword [sum], rax
    mov qword [sum+8], rbx
    
    mov rax, 60
    mov rdi, 0
    syscall
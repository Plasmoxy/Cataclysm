extern _printf

section .data
    numf: db "num=%d", 10
    info: db "eax=%d, ebp=%d, esp=%d", 10

section .text
global _main
_main:
    push ebp
    mov ebp, esp

    ; before call
    push esp
    push ebp
    push eax
    push info
    call _printf
    add esp, 4*4

    call setEax

    ; after call
    push esp
    push ebp
    push eax
    push info
    call _printf
    add esp, 4*4

    mov esp, ebp
    pop ebp
    
    mov eax, 0
ret

setEax:
    mov eax, esp ; let eax be a pointer probe inside function
ret
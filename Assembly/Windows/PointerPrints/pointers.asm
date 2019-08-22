global  _main
extern  _printf
extern _puts

section .data
    numf:        db  'Number = %d', 10, 0
    pointers:    db 'ebp = %d, esp = %d', 10, 0

section .text

_main:
    push    ebp
    mov     ebp, esp

    ; print pointers
    push esp
    push ebp
    push pointers
    call _printf
    add esp, 12

    ; add ebx to eax, eax is now 11
    mov eax, 7
    mov ebx, 4
    add eax, ebx

    ; push eax to stack, esp is now 4 lower
    push eax

    ; print pointers
    push esp
    push ebp
    push pointers
    call _printf
    add esp, 12

    ; print the current number in stack with another push for num format
    push numf
    call _printf
    add esp, 8

    ; esp is now back to normal

    ; print pointers
    push esp
    push ebp
    push pointers
    call _printf
    add esp, 12


    mov     esp, ebp
    pop     ebp
ret

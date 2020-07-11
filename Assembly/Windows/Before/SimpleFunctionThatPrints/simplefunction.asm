extern _printf

section .data
    numf: dw "-> %d", 10

    numA: dw 1
    numB: dw 2

section .text
global _main
_main:
    push ebp
    mov ebp, esp

    sub esp, 4 ; t = [ebp-4]
    push 30
    push 20
    call fadd
    add esp, 8 ; get rid of 2 parameters, end up on third
    
    ; now we are back at return value = third parameter
    ; move it to eax then go back for the third param
    mov eax, [esp]
    add esp, 4

    ; print eax = result
    push eax
    push numf
    call _printf
    add esp, 8

    leave
    mov eax, 0
ret

; add(word a, word b, word result) {
;   result = a + b
; }
; a = ebp+8
; b = ebp+12
; result = ebp+16
fadd:
    push ebp
    mov ebp, esp

    ; store a to eax
    mov eax, [ebp+8]
    
    ; store b to ebx
    mov ebx, [ebp+12]
    
    ; add ebx to eax
    add eax, ebx

    ; store eax to c
    mov [ebp+16], eax

    leave
ret
global ft_strcmp

ft_strcmp:
    xor r10, r10
    xor rax, rax

again:
    mov cl, [rsi + r10] ; me when you cant cmp [rdi + r10], [rsi + r10]
    cmp byte [rdi + r10], cl
    jne noteq
    cmp byte [rsi + r10], 0
    je eq
    inc r10
    jmp again

eq:
    ret

noteq:
    ; have to sign extend since strcmp expects an int return
    movzx rax, byte [rdi + r10]
    movzx r10, byte [rsi + r10]
    sub rax, r10
    ret

; below work, but for char only
; mov al, [rdi + r10]
; sub al, [rsi + r10]

section .note.GNU-stack noalloc noexec nowrite progbits
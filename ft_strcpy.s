global ft_strcpy

ft_strcpy:
    mov rax, rdi ; copy dest to ret value

; armed and dangerous
again:
    mov r10, [rsi] ; cringe, cant do mov [rdi], [rsi]
    mov [rdi], r10
    cmp byte [rsi], 0
    je stop
    inc rdi
    inc rsi
    jmp again

stop:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
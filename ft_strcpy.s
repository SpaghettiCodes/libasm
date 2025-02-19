global ft_strcpy

ft_strcpy:
    xor rcx, rcx
    mov rax, rdi ; copy dest to ret value

; armed and dangerous
again:
    mov dl, [rsi + rcx] ; cringe, cant do mov [rdi], [rsi]
    ; copy into byte register since we are dealing with characters (bytes)
    mov [rdi + rcx], dl
    cmp byte [rsi + rcx], 0
    je stop
    inc rcx
    jmp again

stop:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
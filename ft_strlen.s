global ft_strlen

ft_strlen:
    xor rax, rax ; reset return value to 0

; armed and dangerous
again:
    cmp byte [rdi + rax], 0
    je stop
    add rax, 1
    jmp again

stop:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
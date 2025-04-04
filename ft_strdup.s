global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy
extern __errno_location

ft_strdup:
    ; save input string pointer
    push rdi

    call ft_strlen ; get string length of string
    inc rax ; null terminator

    ; call malloc
    mov rdi, rax
    call malloc wrt ..plt ; wanna check for error here, oops

    ; rax now has the new malloced array
    ; if return value is null, it failed, quit
    cmp rax, 0
    je stop

    ; get back input string pointer
    pop rsi

    ; call ft_strcpy
    mov rdi, rax
    call ft_strcpy

stop:
    ret



section .note.GNU-stack noalloc noexec nowrite progbits
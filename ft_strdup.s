global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy

ft_strdup:
    call ft_strlen ; get string length of string

    mov rdx, rax ; save length

    ; get ready to call malloc
    ; save input string pointer
    mov r8, rdi

    ; call malloc 
    mov rdi, rdx
    call malloc wrt ..plt ; wanna check for error here, oops
    
    ; rax now has the new malloced array

    ; call ft_strcpy
    mov rdi, rax
    mov rsi, r8
    call ft_strcpy

    ; done
    ret


section .note.GNU-stack noalloc noexec nowrite progbits
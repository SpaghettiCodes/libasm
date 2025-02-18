global ft_write
extern __errno_location

ft_write:
    mov rax, 1
    syscall
    ret

; oookay so apparantly syscall does NOT set errno on error
; and we need to set it ourselves

error:

    ; errno location returns the address of errno
    call __errno_location

section .note.GNU-stack noalloc noexec nowrite progbits
global ft_write
extern __errno_location

ft_write:
    mov rax, 1
    syscall
    test eax, eax ; sets sign flag (sf) to 1 if eax is 0
    ret

; oookay so apparantly syscall does NOT set errno on error
; and we need to set it ourselves
; if syscall failed, < 0 is returned, abs of this value is the errno to set

error:

    ; errno location returns the address of errno
    call __errno_location

section .note.GNU-stack noalloc noexec nowrite progbits
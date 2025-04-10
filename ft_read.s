global ft_read
extern __errno_location

ft_read:
    mov rax, 0
    syscall
    test rax, rax ; sets sign flag (sf) to 1 if eax is 0
    js error ; jump if return value is < 0
    ret

; oookay so apparantly syscall does NOT set errno on error
; and we need to set it ourselves
; if syscall failed, < 0 is returned, abs of this value is the errno to set

error:
    neg rax
    push rax
    ; errno location returns the address of errno
    call __errno_location wrt ..plt
    pop rcx
    mov [rax], rcx
    mov rax, -1
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
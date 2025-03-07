global ft_write
extern __errno_location

ft_write:
    mov rax, 1
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

; check what the fuck is plt
; https://stackoverflow.com/questions/28699032/assembly-coding-strdup-malloc-calling-in-shared-library/28699189#28699189

section .note.GNU-stack noalloc noexec nowrite progbits
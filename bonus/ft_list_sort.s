global ft_list_sort

; void	ft_list_sort(t_list **begin_list, int (*cmp)())
; begin list = rdi
; cmp rsi
; rdx cur
; rcx cur2
; r8 prev2

ft_list_sort:
  enter 0, 0
  mov r10, [rdi]
  mov rdx, [rdi + 8]

loop:
  xor r8, r8
  mov rcx, [rdi]

innerloop:
  // check stuff here

  mov r8, rcx
  mov rcx, [rcx + 8]

  mov rdx, [rdx + 8]
  jmp loop

end:
  leave
  ret

section .note.GNU-stack noalloc noexec nowrite progbits
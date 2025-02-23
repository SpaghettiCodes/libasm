global ft_list_size

ft_list_size:
  xor rax, rax

again:
  cmp qword rdi, 0
  je end
  inc rax
  mov qword rdi, [rdi + 8]
  jmp again

end:
  ret

section .note.GNU-stack noalloc noexec nowrite progbits
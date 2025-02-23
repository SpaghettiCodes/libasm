global ft_list_push_front
extern malloc

ft_list_create:
  push rdi

  mov rdi, 16 ; 2 pointers = 8 * 2 = 16 bytes
  call malloc wrt ..plt

  pop rdi
  mov [rax], rdi 
  mov qword [rax + 8], 0

  ret

ft_list_push_front:
  ; save list head pointer
  push rdi

  ; call ft_list_create
  mov rdi, rsi
  call ft_list_create

  ; get list head pointer
  pop rdi

  ; set next value
  mov rdx, [rdi]
  mov [rax + 8], rdx

  ; change list head pointer
  mov [rdi], rax

  ret

section .note.GNU-stack noalloc noexec nowrite progbits
global ft_list_remove_if
extern free

; rdi pointer to first node
; rsi reference data
; rdx compare function
; rcx clear function

; r8 cur
; r9 prev

ft_list_remove_if:
  ; align stack frame, or some function crash when you try calling it
  push rbp
  mov rbp, rsp
  ; theres enter 0, 0 , but its slower

  cmp rdi, 0
  je end

  xor r9, r9
  mov r8, [rdi]

loop:
  cmp r8, 0
  je end

  push rdi
  push rsi
  push rdx
  push rcx
  push r8
  push r9

  mov rdi, [r8]
  call rdx

  pop r9
  pop r8
  pop rcx
  pop rdx
  pop rsi
  pop rdi

  cmp rax, 0
  jne reset

  ; it is, remove the node
  push rdi
  push rsi
  push rdx
  push rcx
  push r8
  push r9

  mov rdi, [r8]
  call rcx 

  pop r9
  pop r8
  pop rcx
  pop rdx
  pop rsi
  pop rdi

  cmp r9, 0
  je first_node

  mov r10, [r8 + 8]
  mov [r9 + 8], r10

  jmp free_go_next

reset:
  mov r9, r8
  mov r8, [r8 + 8]

  jmp loop

first_node:
  mov r10, [r8 + 8]
  mov [rdi], r10

  jmp free_go_next

free_go_next:  
  ; free the node
  push qword [r8 + 8]
  push rdi
  push rsi
  push rdx
  push rcx
  push r10
  push r9

  mov rdi, r8
  call free wrt ..plt 

  pop r9
  pop r10
  pop rcx
  pop rdx
  pop rsi
  pop rdi
  pop r8

  jmp loop

end:
  ; restore stack frame 
  pop rbp
  ; theres leave, but i scare use since i didnt use enter
  ret

section .note.GNU-stack noalloc noexec nowrite progbits 
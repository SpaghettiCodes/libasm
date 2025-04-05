global ft_list_sort

; void	ft_list_sort(t_list **begin_list, int (*cmp)())
; begin list := rdi
; cmp := rsi
; rdx -- cur
; r9  -- endptr
; rcx -- cur2
; r8  -- prev2

; this is insertion sort

ft_list_sort:
  push rbp
  mov rbp, rsp
  ; theres enter 0, 0 , but its slower

  ; if given null, quit
  cmp rdi, 0
  je end

  ; if head is empty, quit
  cmp [rdi], dword 0
  je end

  mov r9, [rdi]
  mov rdx, [r9 + 8]

loop:
  cmp rdx, 0 ; cur = null, end
  je end

  xor r8, r8
  mov rcx, [rdi]

innerloop:
  ; loop to the end and we didnt swap, should be ok, check next element
  ; we should always end at the same node
  cmp rdx, rcx
  je correct_position

  ; check stuff here
  push rdi
  push rsi
  push rdx
  push rcx
  push r9
  push r8

  mov r9, rsi
  mov rdi, [rdx]
  mov rsi, [rcx]
  call r9

  pop r8
  pop r9
  pop rcx
  pop rdx
  pop rsi
  pop rdi

  cmp eax, 0 ; cmp function returns int
  jle insert

next_innerloop:
  ; check next
  mov r8, rcx
  mov rcx, [rcx + 8]
  jmp innerloop

correct_position:
  mov r9, rdx
  mov rdx, [rdx + 8]
  jmp next_loop

insert:
  cmp r8, 0
  je head_insert

  mov [r8 + 8], rdx
  mov r10, [rdx + 8]
  mov [rdx + 8], rcx

  mov [r9 + 8], r10
  jmp next_loop

head_insert:
  mov r10, [rdi]
  mov [rdi], rdx
  mov r11, [rdx + 8]
  mov [rdx + 8], r10

  mov [r9 + 8], r11
  jmp next_loop

next_loop:
  mov rdx, [r9 + 8]
  jmp loop

end:
  pop rbp
  ; theres leave, but i scare use since i didnt use enter
  ret

section .note.GNU-stack noalloc noexec nowrite progbits
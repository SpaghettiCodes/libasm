global ft_atoi_base

; ==========================
; IS_WHITESPACE
; ==========================
; char  := dil

is_whitespace:
  cmp dil, 0x20 ; space
  je is_whitespace_yes

  cmp dil, 0x09 ; tab
  je is_whitespace_yes

  cmp dil, 0x0A ; line feed (\r)
  je is_whitespace_yes

  cmp dil, 0x0B ; vertical feed (\v)
  je is_whitespace_yes

  cmp dil, 0x0C ; form feed (\f)
  je is_whitespace_yes

  cmp dil, 0x0D ; carriage return (\n)
  je is_whitespace_yes

  mov rax, 0
  ret

is_whitespace_yes:
  mov rax, 1
  ret

; ==========================
; CHECK_WHITESPACE
; ==========================
; str   := rdi

check_whitespace:
  cmp [rdi], byte 0
  je check_whitespace_none

  push rdi
  mov dil, byte [rdi]
  call is_whitespace
  pop rdi
  inc rdi

  cmp rax, 1
  je check_whitespace_found

  jmp check_whitespace

check_whitespace_none:
  mov rax, 0
  ret

check_whitespace_found:
  mov rax, 1
  ret

; ==========================
; CHECK_DUPLICATE
; ==========================
; str   := rdi

check_duplicate:
  cmp [rdi], byte 0
  je check_duplicate_end

  mov sil, byte [rdi]
  inc rdi
  push rdi
  call find
  pop rdi
  cmp rax, 0
  jge check_duplicate_fail

  jmp check_duplicate

check_duplicate_end:
  mov rax, 1
  jmp check_duplicate_exit

check_duplicate_fail:
  mov rax, 0
  jmp check_duplicate_exit

check_duplicate_exit:
  ret

; ==========================
; CHECK_BASE
; ==========================
; str   := rdi

check_base:
  ; empty or size of 1
  push rdi
  call strlen
  pop rdi
  cmp rax, 2
  jl nope

  ; check if base contains the same element twice
  push rdi
  call check_duplicate
  pop rdi
  cmp rax, 0
  je nope
  
  ; has + symbol
  mov sil, byte 45 ; '+' symbol
  push rdi
  call find
  pop rdi
  cmp rax, 0
  jge nope

  ; has - symbol
  mov sil, byte 43 ; '-' symbol
  push rdi
  call find
  pop rdi
  cmp rax, 0
  jge nope

  ; has white space symbol
  push rdi
  call check_whitespace
  pop rdi
  cmp rax, 1
  je nope

exit:
  mov rax, 1
  ret

nope:
  mov rax, 0
  ret

; ==========================
; STRLEN
; ==========================
; str   := rdi

strlen:
    xor rax, rax ; reset return value to 0

strlen_again:
    cmp byte [rdi + rax], 0
    je stop
    inc rax
    jmp strlen_again

strlen_stop:
    ret

; ==========================
; FIND
; ==========================
; str     := rdi
; toFind  := sil

find:
  xor rax, rax

loop:
  cmp [rdi + rax], byte 0
  je cant_find

  cmp [rdi + rax], sil
  je stop

  inc rax
  jmp loop

cant_find:
  mov rax, -1

stop:
  ret

; ==========================
; FT_ATOI_BASE
; ==========================
; str   := rdi
; base  := rsi
; -------------------------
; accu     := rax
; base_len := rdx
; sign     := rcx

ft_atoi_base:
  push rdi
  push rsi

  mov rdi, rsi
  call check_base

  pop rsi
  pop rdi

  cmp rax, 0
  je quit

  push rdi
  push rsi

  mov rdi, rsi
  call strlen

  mov rdx, rax
  pop rsi
  pop rdi

  xor rax, rax
  mov rcx, 1

skip_space:
  push rdx
  push rdi
  push rsi

  mov dil, byte [rdi]
  call is_whitespace
  
  pop rsi
  pop rdi
  pop rdx

  cmp rax, 1
  je skip_space_next

  jmp determine_sign

skip_space_next:
  inc rdi
  jmp skip_space

determine_sign:
  cmp [rdi], byte 45 ; "-" symbol
  je flip_sign

  cmp [rdi], byte 43 ; "+" symbol
  je determine_sign_next

  jmp convert_loop

flip_sign:
  imul rcx, -1
  jmp determine_sign_next

determine_sign_next:
  inc rdi
  jmp determine_sign

convert_loop:
  cmp [rdi], byte 0; null term
  je end

  push rdx
  push rcx
  push rdi
  push rsi
  push rax

  mov al, [rdi]
  mov rdi, rsi
  mov sil, al
  call find

  mov r9, rax
  pop rax
  pop rsi
  pop rdi
  pop rcx
  pop rdx

  cmp r9, -1
  je end

  imul rax, rdx
  add rax, r9

convert_loop_next:
  inc rdi
  jmp convert_loop

end:
  imul rax, rcx

quit:
  ret

section .note.GNU-stack noalloc noexec nowrite progbits
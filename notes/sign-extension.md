movzx %al, %dx     # move 8-bit register to 16-bit register. Upper 8 bits of DX set to 0
movzx %al, %edx    # move 8-bit register to 32-bit register. Upper 24 bits of EDX set to 0
                   #     Upper 32 bits of RDX also set to zero because EDX is 32-bit dest
movzx %al, %rdx    # move 8-bit register to 64-bit register. Upper 56 bits of RDX set to 0

movzx %ax, %edx    # move 16-bit register to 32-bit register.Upper 16 bits of EDX set to 0
                   #     Upper 32 bits of RDX also set to zero because EDX is 32-bit dest

#movzx %eax, %rdx  # This instruction doesn't exist. Use mov %eax, %edx

movsx %al, %dx     # Sign extend 8-bit register to 16-bit register
movsx %al, %edx    # Sign extend 8-bit register to 32-bit register
                   #     Upper 32 bits of RDX set to ZERO because EDX is 32-bit dest
movsx %al, %rdx    # Sign extend 8-bit register to 64-bit register

movsx %ax, %edx    # Sign extend 16-bit register to 32-bit register
                   #     Upper 32 bits of RDX set to ZERO because EDX is 32-bit dest
movsx %ax, %rdx    # Sign extend 16-bit register to 64-bit register

movsx %eax, %rdx   # Sign extend 32-bit register to 64-bit register
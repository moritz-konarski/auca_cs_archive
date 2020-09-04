.section .data
message: .string "Hello, World!\n"
m_l: .int 0xE

.section .text

.global main
main:
    mov $0x1, %rax
    mov $0x1, %rdi
    mov m_l(%rip), %rdx
    lea message(%rip), %rsi
    syscall

    xor %eax, %eax
    ret

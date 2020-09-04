.section .data
input_format: .string "%ld"
output_format: .string "%ld\n"

.section .text

fac_n:
    cmp $0x1, %rcx
    jle .fac_n_end
    mov %rcx, %rax
    mul %rsi
    mov %rax, %rsi
    dec %rcx
    call fac_n
    ret

.fac_n_end:
    ret

.global main
main:
    push %rbp
    mov %rsp, %rbp
    sub $0x10, %rsp

    lea input_format(%rip), %rdi
    lea (%rsp), %rsi
    xor %eax, %eax
    call scanf@plt

    mov (%rsp), %rcx
    mov $0x1, %rsi

    call fac_n

    lea output_format(%rip), %rdi
    xor %eax, %eax
    call printf@plt

    add $0x10, %rsp
    leave
    xor %eax, %eax
    ret

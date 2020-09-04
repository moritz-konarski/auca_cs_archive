.section .data
input_format: .string "%ld %ld"
output_format: .string "%ld\n"

.section .text

.gcd_loop:
    cmp $0x0, %rdi
    je .gcd_end
    mov $0x0, %rdx
    mov %rsi, %rax
    div %rdi
    push %rdi
    mov %rdx, %rdi
    pop %rsi
    jmp .gcd_loop

.gcd_end:
    lea output_format(%rip), %rdi
    xor %eax, %eax
    call printf@plt

    add $0x10, %rsp
    leave
    xor %eax, %eax
    ret

.global main
main:
    push %rbp
    mov %rsp, %rbp
    sub $0x10, %rsp

    lea input_format(%rip), %rdi
    lea 0x8(%rsp), %rsi
    lea (%rsp), %rdx
    xor %eax, %eax
    call scanf@plt

    mov 0x8(%rsp), %rsi
    mov (%rsp), %rdi

    jmp .gcd_loop

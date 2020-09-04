.section .data
input_format: .string "%ld %ld"
output_format: .string "%ld\n"

.section .text

gcd: 
    # if b == 0
    cmp $0x0, %rdi
    # return
    je .gcd_end
    # prepare the dividend
    mov $0x0, %rdx
    # part of the dividend will be a
    mov %rsi, %rax
    # divide a by b
    div %rdi
    # move the remainder to stack
    push %rdx
    # move a to b
    mov %rdi, %rsi
    pop %rdi
    call gcd
    jmp .gcd_end

.gcd_end:
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

    call gcd

    lea output_format(%rip), %rdi
    xor %eax, %eax
    call printf@plt

    add $0x10, %rsp
    leave
    xor %eax, %eax
    ret

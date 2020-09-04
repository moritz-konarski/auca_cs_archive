.section .data
output_format: .string "%ld\n"

.section .text

sum_10:
    pop %rdx
    xor %rsi, %rsi
    pop %rax
    add %rax, %rsi
    pop %rax
    add %rax, %rsi
    pop %rax
    add %rax, %rsi
    pop %rax
    add %rax, %rsi
    pop %rax
    add %rax, %rsi
    pop %rax
    add %rax, %rsi
    pop %rax
    add %rax, %rsi
    pop %rax
    add %rax, %rsi
    pop %rax
    add %rax, %rsi
    pop %rax
    add %rax, %rsi
    push %rdx
    ret

.global main
main:

    push %rbp
    mov %rsp, %rbp
    
    push $1
    push $2
    push $3
    push $4
    push $5
    push $6
    push $7
    push $8
    push $9
    push $10
    call sum_10

    lea output_format(%rip), %rdi
    xor %eax, %eax
    call printf@plt

    leave
    xor %eax, %eax
    ret

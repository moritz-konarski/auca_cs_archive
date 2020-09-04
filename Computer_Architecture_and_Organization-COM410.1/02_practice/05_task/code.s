.section .data
a: .int 0,0
b: .int 0,0
input_format: .string "%ld %ld"
output_format: .string "%ld\n"

.section .text

.global main
main:
    push %rbp
    mov %rsp, %rbp
    
    lea input_format(%rip), %rdi
    lea a(%rip), %rsi
    lea b(%rip), %rdx
    xor %eax, %eax
    call scanf@plt

    mov a(%rip), %rsi
    mov b(%rip), %rax

    add %rax, %rsi

    lea output_format(%rip), %rdi
    xor %eax, %eax
    call printf@plt

    leave
    xor %eax, %eax
    ret

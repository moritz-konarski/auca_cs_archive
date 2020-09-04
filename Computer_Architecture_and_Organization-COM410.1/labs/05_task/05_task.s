.section .data
input_format: .string "%ld %ld"
output_format: .string "%ld + %ld = %ld\n"
a: .int 0, 0
b: .int 0, 0

.section .text
.global main
main:

    # try to align the base pointer
    sub $0x8, %rsp

    lea input_format(%rip), %rdi    # set input format
    lea a(%rip), %rsi
    lea b(%rip), %rdx
    xor %eax, %eax
    call scanf@plt

    mov a(%rip), %rsi
    mov b(%rip), %rdx
    mov %rdx, %rcx
    add %rsi, %rcx

    lea output_format(%rip), %rdi
    xor %eax, %eax
    call printf@plt

    # re-align the base pointer
    add $0x8, %rsp

    xor %eax, %eax
    ret

.section .data
a: .int 0,0
input_format: .string "%ld"
output_format: .string "%ld\n"

.section .text

.global main
main:
    sub $0x8, %rsp
    lea input_format(%rip), %rdi
    lea a(%rip), %rsi
    xor %eax, %eax
    call scanf@plt

    mov a(%rip), %rsi
    inc %rsi

    lea output_format(%rip), %rdi
    xor %eax, %eax
    call printf@plt

    add $0x8, %rsp
    xor %eax, %eax
    ret

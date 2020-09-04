.section .data
a: .int 0, 0
b: .int 0, 0
in_format: .string "%ld %ld"
out_format: .string "gcd(%ld, %ld) = %ld\n"

.section .text
.global main
main:
    push %rpb
    mov %rsp, %rbp

    lea in_format(%rip), %rsi
    lea a(%rip), %rdi
    lea b(%rip), %rdx
    xor %eax, %eax
    call printf@plt

    mov a(%rip), %rax # a
    mov b(%rip), %rdx # b,  %rsi is temp

gcd:
    test %rdx, %rdx
    jz .return_a



# else return gcd(b, a mod b)

.return_a:
    # some code

.end:
    leave
    xor %eax, %eax
    ret

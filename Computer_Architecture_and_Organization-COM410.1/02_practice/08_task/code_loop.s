.section .data
n: .int 0,0
input_format: .string "%ld"
output_format: .string "%ld\n"

.section .text

.fib_loop:
    cmp $0x1, %rax
    jle .fib_end
    push %rsi
    add %rdi, %rsi
    pop %rdi
    dec %rax
    jmp .fib_loop

.fib_end:
    lea output_format(%rip), %rdi
    xor %eax, %eax
    call printf@plt

    leave
    xor %eax, %eax
    ret

.global main
main:   
    push %rbp
    mov %rsp, %rbp

    lea input_format(%rip), %rdi
    lea n(%rip), %rsi
    xor %eax, %eax
    call scanf@plt

    mov n(%rip), %rax
    mov $0x0, %rdi
    mov $0x1, %rsi

    jmp .fib_loop


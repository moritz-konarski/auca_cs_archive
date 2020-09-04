.section .data
n: .int 0,0
input_format: .string "%ld"
output_format: .string "%ld\n"

.section .text

fib_n:
    cmp $0x1, %rax
    jle .fib_n_end
    
    push %rsi
    add  %rdx, %rsi
    pop %rdx
    dec %rax
    call fib_n
    jmp .fib_n_end

.fib_n_end:
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
    mov $0x0, %rdx
    mov $0x1, %rsi

    call fib_n

    lea output_format(%rip), %rdi
    xor %eax, %eax
    call printf@plt

    leave
    xor %eax, %eax
    ret

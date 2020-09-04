.section .data
input_format: .string "Please enter 4 large integers:\n%ld %ld %ld %ld"
a: .int 0, 0
b: .int 0, 0
m: .int 0, 0
seed: .int 0, 0
output_format: .string "%ld \n"

array:          # array of size 10
    .quad 0, 1, 2, 3, 4, 5, 6, 7, 8, 9

.section .text
.global main
main:
    push %rbp
    mov %rsp, %rbp

    lea input_format(%rip), %rdi
    lea a(%rip), %rsi
    lea b(%rip), %rdx
    lea m(%rip), %rcx
    lea seed(%rip), %r8
    xor %eax, %eax
    call scanf@plt

    lea array(%rip), %r10
    xor %rax, %rax
    mov $10, %rdx
    jmp .print_loop

.print_loop:
    cmp $10, %rax
    jge .end
    mov %r10, %rsi
    lea output_format(%rip), %rdi
    xor %eax, %eax
    call printf@plt
    inc %rax
    jmp .print_loop

.end:
    leave
    xor %eax, %eax
    ret
    

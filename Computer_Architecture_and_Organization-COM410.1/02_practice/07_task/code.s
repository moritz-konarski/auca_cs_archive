.section .data
input_format: .string "%ld %ld"
a_gr_b: .string "%ld is greater than %ld\n"
a_le_b: .string "%ld is less than %ld\n"
a_eq_b: .string "%ld is equal to %ld\n"
a: .int 0,0
b: .int 0,0

.section .text

.a_gr_b:
    lea a_gr_b(%rip), %rdi
    jmp .print_end

.a_le_b:
    lea a_le_b(%rip), %rdi
    jmp .print_end

.a_eq_b:
    lea a_eq_b(%rip), %rdi
    jmp .print_end

.print_end:
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
    lea a(%rip), %rsi
    lea b(%rip), %rdx
    xor %eax, %eax
    call scanf@plt

    mov a(%rip), %rsi
    mov b(%rip), %rdx

    cmp %rdx, %rsi
    jg .a_gr_b
    je .a_eq_b
    jmp .a_le_b

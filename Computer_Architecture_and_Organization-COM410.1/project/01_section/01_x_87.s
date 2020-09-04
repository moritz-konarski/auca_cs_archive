.section .data

input_message:   .string "Please enter 4 large numbers:\n"
input_format:    .string "%ld %ld %ld %ld"
output_rand_arr: .string "\n24 random array elements:\n"      # arr_len
output_sort_arr: .string "\n24 sorted array elements:\n"      # arr_len
output_format:   .string "%ld\n"
out_average:     .string "average       = %ld\n"
out_sum:         .string "sum           = %ld\n"
out_geom_sum:    .string "geometric sum = %ld\n"
a: .int 0, 0
x: .int 0, 0
b: .int 0, 0
m: .int 0, 0

array_length: .long 24


.section .text

# generate random numbers with lcg
# uses r11, r12, r8, rcx, rdx
generate_random_array:
	mov $0, %r12                # initialize counter
.rng_loop:
	cmp  array_length(%rip), %r12
	jge .rng_loop_end
    mov (%r11, %r12, 8), %rax   # get array element X_{n}
    mul %rdi                    # multiply by a
    add %r8, %rax               # add b
    div %rcx                    # divide by m to find mod m
    mov %rdx, 8(%r11, %r12, 8)  # store X_{n+1}
	inc %r12                    # increase the counter
	jmp .rng_loop
.rng_loop_end:
	ret

# print the whole array
# uses r12, rdi, rsi, rax
print_array:
	mov  $1, %r12                       # initialize counter
.print_loop:
	cmp  array_length(%rip), %r12       # arr_len - 1, check counter
	jg   .print_loop_end
	lea  output_format(%rip), %rdi	    # load output format
	mov  (%rbp, %r12, 8), %rsi          # load array value
	xor  %eax, %eax
	call printf@plt
	inc  %r12
	jmp .print_loop
.print_loop_end:
    ret

# sort the array using a very inefficient bubble sort implementation
# outer loop index: r11
# index: r12
# regs for comparison: r8, r9
bubble_sort_array:
    mov $0, %r11                    # initialize outer counter
.outer_sort_loop:
    cmp array_length(%rip), %r11    # check outer counter
    jge .outer_sort_loop_end
    mov $1, %r12                    # initialize inner loop
.sort_loop:
    cmp array_length(%rip), %r12    # check inner counter
    jge .sort_loop_end
    mov (%rbp, %r12, 8), %r8        # get first array element, index is inner counter
    mov 8(%rbp, %r12, 8), %r9       # get second array element
    cmp %r8, %r9                    # compare them
    jge .sort_not_needed            # if second > first, do nothing
    mov %r8, 8(%rbp, %r12, 8)       # else: switch them around
    mov %r9, (%rbp, %r12, 8)        # ---
.sort_not_needed:
    inc %r12
    jmp .sort_loop
.sort_loop_end:
    inc %r11
    jmp .outer_sort_loop
.outer_sort_loop_end:
    ret

# find average
# uses r12, rsi
# returns rsi
find_arr_average:
    mov    $1, %r12
    fldz                                # load 0
.average_loop:
    cmp    array_length(%rip), %r12     # check counter
    jg     .average_loop_end
    fildq  (%rbp, %r12, 8)              # load array element
    faddp  %st, %st(1)                  # add to sum
    inc    %r12
    jmp    .average_loop
.average_loop_end:
    fildq   array_length(%rip)          # load array length
    fdivr  %st(1), %st                  # find average
    fistpq -16(%rbp)                    # store to memory
    mov    -16(%rbp), %rsi              # store to register
    ret

# find sum
# uses rsi, r12
# returns rsi
find_arr_sum:
    mov    $1, %r12
    fldz                                # load 0
.sum_loop:
    cmp    array_length(%rip), %r12
    jg     .sum_loop_end
    fildq  (%rbp, %r12, 8)              # laod array element
    faddp  %st, %st(1)                  # add element to sum
    inc    %r12
    jmp    .sum_loop
.sum_loop_end:
    fistpq -16(%rbp)                    # store to memory
    mov    -16(%rbp), %rsi              # store to register
    fst    %st
    ret

# find geometric sum
# uses: rsi, r12, r8
# returns rsi
find_arr_geom_sum:
    mov    $1, %r12                     # init counter
    mov    $1, %r8                      # initialze exponent
    fldz                                # load 0
.geom_sum_loop:
    cmp    array_length(%rip), %r12
    jg     .geom_sum_loop_end
    fildl  (%rbp, %r12, 8)              # load array element
    mov    %r8, -16(%rbp)               # load exponent
    fildq  -16(%rbp)
    fmulp  %st, %st(1)                  # multiply element by exponent
    faddp  %st, %st(1)                  # add result to sum
    inc    %r12
    shl    $1, %r8                      # increase exponent
    jmp    .geom_sum_loop
.geom_sum_loop_end:
    fistpq -16(%rbp)                    # store to memeory
    mov    -16(%rbp), %rsi              # store to register
    ret


.global main
main:
	sub  $8, %rsp
# print message about inputting numbers
    lea  input_message(%rip), %rdi
    xor  %eax, %eax
    call printf@plt

# read a, x, c, m from cli
	lea  input_format(%rip), %rdi
	lea  a(%rip), %rsi
	lea  x(%rip), %rdx
	lea  b(%rip), %rcx
	lea  m(%rip), %r8
	xor  %eax, %eax
	call scanf@plt

# reserve space for array
    mov array_length(%rip), %rax
    mov $8, %r8
    mul %r8
	sub  %rax, %rsp          # 8 * arr_len, make space for array

	push %rbp                # align stack pointers
	mov  %rsp, %rbp

# move variables
	mov  a(%rip), %rdi       # rdi is a
	mov  x(%rip), %r11       # r11 is x
	mov  %r11, 8(%rbp)       # make local copy of x
	lea  8(%rbp), %r11       # 8(%rbp) is arr[0], r11 is pointer to it
	mov  b(%rip), %r8        # r8 is b
	mov  m(%rip), %rcx       # rcx is m


# print random array
	call generate_random_array
    lea  output_rand_arr(%rip), %rdi
    xor  %eax, %eax
    call printf@plt
    call print_array

# print sorted array
    call bubble_sort_array
    lea  output_sort_arr(%rip), %rdi
    xor  %eax, %eax
    call printf@plt
    call print_array

# find and print sum
    call find_arr_sum
    lea  out_sum(%rip), %rdi
    xor  %eax, %eax
    call printf@plt

# find and print average
    call find_arr_average
    lea  out_average(%rip), %rdi
    xor  %eax, %eax
    call printf@plt

# find and print geometric sum
    call find_arr_geom_sum
    lea  out_geom_sum(%rip), %rdi
    xor  %eax, %eax
    call printf@plt

# remove space for array
    mov array_length(%rip), %rax
    mov $8, %r8
    mul %r8
    add $8, %rax

# exit program
	leave
	add  %rax, %rsp                 # 8 * arr_len + 8, remove local vars
	xor  %eax, %eax
	ret

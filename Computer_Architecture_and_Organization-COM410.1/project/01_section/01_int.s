.section .data

input_message:   .string "Please enter 4 large numbers:\n"
input_format:    .string "%ld %ld %ld %ld"
output_rand_arr: .string "\n24 random array elements:\n"      # arr_len
output_sort_arr: .string "\n24 sorted array elements:\n"      # arr_len
output_format:   .string "%ld\n"
out_max:         .string "\nmax           = %ld\n"
out_min:         .string "min           = %ld\n"
out_average:     .string "average       = %ld\n"
out_mode:        .string "mode          = %ld\n"
out_sum:         .string "sum           = %ld\n"
out_geom_sum:    .string "geometric sum = %ld\n"
out_median:      .string "median        = %ld\n"
a: .int 0, 0
x: .int 0, 0
b: .int 0, 0
m: .int 0, 0

array_length: .long 24

.section .text

# function to generate random numbers using lcg
generate_random_array:
	mov $0, %r12                        # initialize counter
.rng_loop:
	cmp  array_length(%rip), %r12
	jge .rng_loop_end
    mov (%r11, %r12, 8),     %rax       # get array element X_{n}
    mul %rdi                            # multiply by a
    add %r8, %rax                       # add b
    div %rcx                            # divide by m to find mod m
    mov %rdx, 8(%r11, %r12, 8)          # store X_{n+1}
	inc %r12                            # increase the counter
	jmp .rng_loop
.rng_loop_end:
	ret

# print the whole array
print_array:
	mov  $1, %r12                       # initialize counter
.print_loop:
	cmp  array_length(%rip),  %r12
	jg  .print_loop_end
	lea  output_format(%rip), %rdi	    # load output format
	mov  (%rbp, %r12, 8),     %rsi      # load array value
	xor  %eax, %eax
	call printf@plt
	inc  %r12
	jmp  .print_loop
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

# rsi has the result, r8 for comparison, r12 index
find_arr_max:
    mov $1, %r12                    # initialize counter
    mov (%rbp, %r12, 8), %rsi       # put first element into max
    inc %r12
.max_loop:
    cmp array_length(%rip), %r12    # check counter
    jg  .max_loop_end
    mov (%rbp, %r12, 8), %r8        # get element to compare
    inc %r12
    cmp %r8, %rsi                   # compare element and max
    jge .max_loop                   # if max is greater, do nothing
    mov %r8, %rsi                   # else switch them around
    jmp .max_loop
.max_loop_end:
    ret

# rsi has the result, r8 for comparison, r12 index
find_arr_min:
    mov $1, %r12                    # initalize counter
    mov (%rbp, %r12, 8), %rsi       # get first element
    inc %r12
.min_loop:
    cmp array_length(%rip), %r12
    jg .min_loop_end
    mov (%rbp, %r12, 8), %r8        # get element to compare
    inc %r12
    cmp %r8, %rsi                   # compare element to min
    jle .min_loop
    mov %r8, %rsi                   # if smaller, switch
    jmp .min_loop
.min_loop_end:
    ret

# rsi has result, r8 as sum, r12 index
find_arr_average:
    mov $1, %r12                    # initialize counter
    mov (%rbp, %r12, 8), %r8        # get first element
    inc %r12
.average_loop:
    cmp array_length(%rip), %r12    # check counter
    jg  .average_loop_end
    add (%rbp, %r12, 8), %r8        # add element to sum
    inc %r12
    jmp .average_loop
.average_loop_end:
    mov %r8, %rax                   # move sum for division
    mov array_length(%rip), %r8     # get array length
    div %r8                         # find average
    mov %rax, %rsi                  # store
    ret

# rsi as mode, r8 as value, r9 as count, r10 as high count, r12 outer index,
# r11 inner index, %rcx for comparison
find_arr_mode:
    mov $1, %r12                    # initialze outer counter
    mov $0, %r10                    # initialize count of common element
.mode_loop:
    cmp array_length(%rip), %r12    # check counter
    jg  .mode_loop_end
    mov (%rbp, %r12, 8), %r8        # get array element
    mov $0, %r9                     # initlize count for this element
    mov $1, %r11                    # initialize inner counter
.inner_mode_loop:
    cmp array_length(%rip), %r11    # check inner counter
    jg  .inner_mode_loop_end
    mov (%rbp, %r11, 8), %rcx       # get array element
    cmp %rcx, %r8                   # compare with current counted element
    jne .mode_not_equal
    inc %r9                         # if equal, increase count
.mode_not_equal:
    inc %r11
    jmp .inner_mode_loop
.inner_mode_loop_end:
    inc %r12                        # increase outer index
    cmp %r10, %r9                   # check if current counted element is larger than overall max
    jle .mode_loop
    mov %r9, %r10                   # if yes, update the overall tracking registers
    mov %r8, %rsi                   # ---
    jmp .mode_loop
.mode_loop_end:
    ret

# rsi has sum, r12 index
find_arr_sum:
    mov $1, %r12                    # init counter
    mov (%rbp, %r12, 8), %rsi       # get first element
    inc %r12                        #
.sum_loop:
    cmp array_length(%rip), %r12
    jg  .sum_loop_end
    add (%rbp, %r12, 8), %rsi       # add current element to sum
    inc %r12
    jmp .sum_loop
.sum_loop_end:
    ret

# rsi has result, only viable after sorting
find_arr_median:
    mov array_length(%rip), %r12    # get array length
    mov %r12, %rax                  # find middle index
    mov $2, %rsi
    div %rsi
    cmp $0, %rdx
    je  .median_even_len
    mov (%rbp, %rax, 8), %rsi
    jmp .median_end
.median_even_len:
    mov (%rbp, %rax, 8), %rsi      # retrieve middle element
    add 8(%rbp, %rax, 8), %rsi
    shr $1, %rsi
.median_end:
    ret

# rsi has sum, r12 index, r8 exponent, r9 temp
find_arr_geom_sum:
    mov $1, %r12
    mov (%rbp, %r12, 8), %rsi       # get first element
    inc %r12
    mov $2, %r8                     # initialize exponent
.geom_sum_loop:
    cmp array_length(%rip), %r12
    jg  .geom_sum_loop_end
    mov (%rbp, %r12, 8), %rax       # load array element
    mul %r8                         # multiply by exponent
    add %rax, %rsi                  # add to sum
    inc %r12
    shl $1, %r8                     # increase exponent
    jmp .geom_sum_loop
.geom_sum_loop_end:
    ret


.global main
main:
	sub $8, %rsp            # make space for local variable

# print message about inputting numbers
    lea  input_message(%rip), %rdi
    xor  %eax, %eax
    call printf@plt

# read a, x, b, m from cli
	lea  input_format(%rip), %rdi
	lea  a(%rip), %rsi
	lea  x(%rip), %rdx
	lea  b(%rip), %rcx
	lea  m(%rip), %r8
	xor  %eax, %eax
	call scanf@plt

# prepare offset for array memory
    mov array_length(%rip), %rax
    mov $8, %r8
    mul %r8
	sub  %rax, %rsp

	push %rbp               # align stack pointers
	mov  %rsp, %rbp

# move variables to registers
	mov  a(%rip), %rdi       # rdi is a
	mov  x(%rip), %r11       # r11 is x
	mov  %r11, 8(%rbp)       # make local copy of x
	lea  8(%rbp), %r11       # 8(%rbp) is arr[0], r11 is pointer to it
	mov  b(%rip), %r8        # r8 is b
	mov  m(%rip), %rcx       # rcx is m


# generate and print random array
	call generate_random_array
    lea  output_rand_arr(%rip), %rdi
    xor  %eax, %eax
    call printf@plt
    call print_array

# sort and print array
    call bubble_sort_array
    lea  output_sort_arr(%rip), %rdi
    xor  %eax, %eax
    call printf@plt
    call print_array

# find and print array max
    call find_arr_max
    lea  out_max(%rip), %rdi
    xor  %eax, %eax
    call printf@plt

# find and print array min
    call find_arr_min
    lea  out_min(%rip), %rdi
    xor  %eax, %eax
    call printf@plt

# find and print array average
    call find_arr_average
    lea  out_average(%rip), %rdi
    xor  %eax, %eax
    call printf@plt

# find and print array mode
    call find_arr_mode
    lea  out_mode(%rip), %rdi
    xor  %eax, %eax
    call printf@plt

# find and print array sum
    call find_arr_sum
    lea  out_sum(%rip), %rdi
    xor  %eax, %eax
    call printf@plt

# find and print array median
    call find_arr_median
    lea  out_median(%rip), %rdi
    xor  %eax, %eax
    call printf@plt

# find and print array geometric sum
    call find_arr_geom_sum
    lea  out_geom_sum(%rip), %rdi
    xor  %eax, %eax
    call printf@plt

    mov array_length(%rip), %rax
    mov $8, %r8
    mul %r8
    add $8, %rax

# exit program
	leave
	add  %rax, %rsp
	xor  %eax, %eax
	ret

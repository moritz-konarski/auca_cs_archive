/*
 *  x_87 version of the project
 */
#include "iostream"

#define SIZE 60         // must be divisible by 12

void print_array(long *array_1, long *array_2, long *array_3, long *array_4, long *array_5) {
    std::cout << "       a       |       b       |       c       |       d       |       e       |" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        printf("%14ld |", array_1[i]);  // a
        printf("%14ld |", array_2[i]);  // b
        printf("%14ld |", array_3[i]);  // c
        printf("%14ld |", array_4[i]);  // c
        printf("%14ld |", array_5[i]);  // c
        std::cout << std::endl;
    }
}

void section_a(long *array, long a, long b, long m) {
    for (int i = 0; i < SIZE - 1; ++i) {
        __asm__ __volatile__ (
        "mul  %%rdi;"           // multiply by a
        "add  %%rsi, %%rax;"    // add b
        "div  %%rcx;"           // divide by m
        "mov  %%rdx, %0;"       // store
        : "=m"(array[i + 1])
        : "a"(array[i]), "D"(a), "S"(b), "c"(m)
        );
    }
}

// take new_array = array * c + d
// using c, d as ints
void section_b(long *array, long *new_array, long e, long f) {
    for (int i = 0; i < SIZE; ++i) {
        __asm__ __volatile__ (
        "fildq  %1;"                // load array[i]
        "fildq  %3;"                // load c
        "fmulp  %%st, %%st(1);"     // multiply array by c
        "fildq  %2;"                // load b
        "faddp  %%st, %%st(1);"     // add b to result
        "fistpq %0;"                // store
        : "=m"(new_array[i])
        : "m"(array[i]), "m"(e), "m"(f)
        );
    }
}

// new_array[i]   = 0.393 * array[i] + 0.769 * array[i+1] + 0.189 * array[i+2]
// new_array[i+1] = 0.349 * array[i] + 0.686 * array[i+1] + 0.168 * array[i+2]
// new_array[i+2] = 0.272 * array[i] + 0.534 * array[i+1] + 0.131 * array[i+2]
void section_c(long *array, long *new_array) {
    double constants[] = {0.393f, 0.769f, 0.189f,
                          0.349f, 0.686f, 0.168f,
                          0.272f, 0.534f, 0.131f};

    for (long i = 0; i < SIZE; i += 3) {
        for (long j = 0; j < 3; ++j) {
            __asm__ __volatile__ (
            "fldl   (%%rcx,   %%rsi, 8);"   // load first constant
            "fildq  (%%rax,   %%rdi, 8);"   // load fist array element
            "fmulp  %%st(1),  %%st;"        // multiply them

            "fldl   8(%%rcx,  %%rsi, 8);"   // load second constant
            "fildq  8(%%rax,  %%rdi, 8);"   // load second array element
            "fmulp  %%st(1),  %%st;"        // multiply them
            "faddp  %%st(1),  %%st;"        // add first to second result

            "fldl   16(%%rcx, %%rsi, 8);"   // load third constant
            "fildq  16(%%rax, %%rdi, 8);"   // load third array element
            "fmulp  %%st(1),  %%st;"        // multiply them
            "faddp  %%st(1),  %%st;"        // add results

            "fistpq (%%rbx,   %%rdx, 8);"   // store
            ::"a"(array), "b"(new_array), "c"(constants), "d"(i + j), "S"(3 * j), "D"(i)
            );
        }
    }
}

// new_array[i] = (array[i] + array[i+1] + array[i+2]) / 3
void section_d(long *array, long *new_array) {
    int num_3 = 3;
    for (long i = 0; i < SIZE - 2; ++i) {
        __asm__ __volatile__ (
        "fildq  (%%rdx,   %%rax, 8);"   // load array[i]
        "fildq  8(%%rdx,  %%rax, 8);"   // load array[i+1]
        "fildq  16(%%rdx, %%rax, 8);"   // load array[i+2]

        "faddp  %%st,     %%st(1);"     // add first two
        "faddp  %%st,     %%st(1);"     // add third to first result
        "fidiv  %3;"                    // divide by 3

        "fistpq %0;"                    // store result
        : "=m"(new_array[i])
        : "d"(array), "a"(i), "m"(num_3)
        );
    }

    // second to last case
    __asm__ __volatile__ (
    "fildq  (%%rdx,   %%rax, 8);"   // load array[i]
    "fildq  8(%%rdx,  %%rax, 8);"   // load array[i+1]
    "fildq  (%%rdx, %%rbx, 8);"   // load array[i+2]

    "faddp  %%st,     %%st(1);"     // add first two
    "faddp  %%st,     %%st(1);"     // add third to first result
    "fidiv  %3;"                    // divide by 3

    "fistpq %0;"                    // store result
    : "=m"(new_array[SIZE-2])
    : "d"(array), "a"(SIZE-2), "m"(num_3), "b"(0)
    );

    // second to last case
    __asm__ __volatile__ (
    "fildq  (%%rdx,   %%rax, 8);"   // load array[i]
    "fildq  (%%rdx,  %%rbx, 8);"   // load array[i+1]
    "fildq  8(%%rdx, %%rbx, 8);"   // load array[i+2]

    "faddp  %%st,     %%st(1);"     // add first two
    "faddp  %%st,     %%st(1);"     // add third to first result
    "fidiv  %3;"                    // divide by 3

    "fistpq %0;"                    // store result
    : "=m"(new_array[SIZE-1])
    : "d"(array), "a"(SIZE-1), "m"(num_3), "b"(0)
    );
}

// new_array[i] = array[i] * ((255 / d / 2) * c) - array[i-1]
void section_e(long *array, long *new_array, long e, long f) {
    long num_2 = 2;
    long num_255 = 255;

    // case i = 0
    __asm__ __volatile__ (
    "fildq   %4;"                       // load b
    "fildq   %7;"                       // load 255
    "fdivp   %%st,     %%st(1);"        // divide 255 by b

    "fildq   %6;"                       // load 2
    "fdivrp  %%st,     %%st(1);"        // divide result by 2

    "fildq   %5;"                       // load c
    "fmulp   %%st,     %%st(1);"        // multiply result by c

    "fildq   (%%rdx,   %%rax, 8);"      // load array[i]
    "fmulp   %%st,     %%st(1);"        // multipy result by array[i]

    "fildq   (%%rdx,   %%rbx, 8);"      // load array[i-1]
    "fsubrp  %%st,     %%st(1);"        // subtract array[i-1] from result

    "fistpq  %0;"                       // store result
    : "=m"(new_array[0])
    : "d"(array), "a"(0), "b"(SIZE-1), "m"(e), "m"(f), "m"(num_2), "m"(num_255)
    );

    for (long i = 1; i < SIZE; ++i) {
        __asm__ __volatile__ (
        "fildq   %3;"                       // load b
        "fildq   %6;"                       // load 255
        "fdivp   %%st,     %%st(1);"        // divide 255 by b

        "fildq   %5;"                       // load 2
        "fdivrp  %%st,     %%st(1);"        // divide result by 2

        "fildq   %4;"                       // load c
        "fmulp   %%st,     %%st(1);"        // multiply result by c

        "fildq   (%%rdx,   %%rax, 8);"      // load array[i]
        "fmulp   %%st,     %%st(1);"        // multipy result by array[i]

        "fildq   -8(%%rdx, %%rax, 8);"      // load array[i-1]
        "fsubrp  %%st,     %%st(1);"        // subtract array[i-1] from result

        "fistpq  %0;"                       // store result
        : "=m"(new_array[i])
        : "d"(array), "a"(i), "m"(e), "m"(f), "m"(num_2), "m"(num_255)
        );
    }
}


int main(int argc, char **argv) {
    //   m  d  a  s  c  d
    long a, x, b, m, e, f;
    long array_a[SIZE], array_b[SIZE], array_c[SIZE], array_d[SIZE], array_e[SIZE];
    std::cout << "Please enter 6 large numbers (a, x, b, m, e, f):" << std::endl;
    std::cin >> a >> x >> b >> m >> e >> f;
    array_a[0] = x;

    section_a(array_a, a, b, m);
    section_b(array_a, array_b, e, f);
    section_c(array_a, array_c);
    section_d(array_a, array_d);
    section_e(array_a, array_e, e, f);
    print_array(array_a, array_b, array_c, array_d, array_e);

    return 0;
}

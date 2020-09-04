/*
 *  simd version of the project
 */
#include "iostream"

#define SIZE 60 // must be divisible by 3 and 4

void print_array(int *array_1, int *array_2, int *array_3, int *array_4, int *array_5) {
    std::cout << "       a       |       b       |       c       |       d       |       e       |" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        printf("%14d |", array_1[i]);  // a
        printf("%14d |", array_2[i]);  // b
        printf("%14d |", array_3[i]);  // c
        printf("%14d |", array_4[i]);  // d
        printf("%14d |", array_5[i]);  // e
        std::cout << std::endl;
    }
}

void section_a(int *array, int a, int b, int m) {
    for (int i = 0; i < SIZE - 1; ++i) {
        __asm__ __volatile__ (
        "mul  %%edi;"           // multiply by a
        "add  %%esi, %%eax;"    // add b
        "div  %%ecx;"           // divide by m
        "mov  %%edx, %0;"       // store result
        : "=m"(array[i + 1])
        : "a"(array[i]), "D"(a), "S"(b), "c"(m)
        );
    }
}

// take new_array = array * c + d
void section_b(int *array, int *new_array, int e, int f) {
    for (int i = 0; i < SIZE; i += 4) {
        __asm__ __volatile__ (
        "vmovdqa       %1,      %%xmm0;"            // load array
        "cvtdq2ps      %%xmm0,  %%xmm0;"            // convert array
        "vpbroadcastd  %2,      %%xmm1;"            // broadcast b
        "vpbroadcastd  %3,      %%xmm2;"            // broadcast c
        "vfmadd132ps   %%xmm0,  %%xmm1, %%xmm2;"    // array * c + b = c
        "vmovdqa       %%xmm2,  %0;"                // return c
        : "=m"(new_array[i])
        : "m"(array[i]), "g"(e), "g"(f)
        : "%xmm0", "%xmm1", "%xmm2"
        );
    }
}

// new_array[i]   = 0.393 * array[i] + 0.769 * array[i+1] + 0.189 * array[i+2]
// new_array[i+1] = 0.349 * array[i] + 0.686 * array[i+1] + 0.168 * array[i+2]
// new_array[i+2] = 0.272 * array[i] + 0.534 * array[i+1] + 0.131 * array[i+2]
void section_c(int *array, int *new_array) {
    float constants[] = {0.393f, 0.769f, 0.189f,
                         0.349f, 0.686f, 0.168f,
                         0.272f, 0.534f, 0.131f};

    for (int i = 0; i < SIZE; i += 3) {
        for (int j = 0; j < 3; ++j) {
            __asm__ __volatile__ (
            "movss    (%%rcx, %%rsi,  4), %%xmm0;"  // load first constant
            "movd     (%%rax, %%rdi,  4), %%xmm1;"  // load fist array element
            "cvtdq2ps %%xmm1, %%xmm1;"              // convert to float
            "vmulps   %%xmm0, %%xmm1, %%xmm2;"      // multiply

            "movss    4(%%rcx, %%rsi, 4), %%xmm0;"  // load second constant
            "movd     4(%%rax, %%rdi, 4), %%xmm1;"  // load second array element
            "cvtdq2ps %%xmm1, %%xmm1;"              // convert to float
            "vmulps   %%xmm0, %%xmm1, %%xmm3;"      // multiply

            "movss    8(%%rcx, %%rsi, 4), %%xmm0;"  // load third constant
            "movd     8(%%rax, %%rdi, 4), %%xmm1;"  // load third array element
            "cvtdq2ps %%xmm1, %%xmm1;"              // convert to float
            "vmulps   %%xmm0, %%xmm1, %%xmm4;"      // multiply

            "vaddps   %%xmm4, %%xmm3, %%xmm1;"      // add two results
            "vaddps   %%xmm2, %%xmm1, %%xmm0;"      // add two results

            "cvtps2dq %%xmm0, %%xmm0;"              // convert to int
            "movd     %%xmm0, (%%rbx, %%rdx, 4);"   // store
            ::"a"(array), "b"(new_array), "c"(constants), "d"(i + j), "S"(3 * j), "D"(i)
            : "%xmm0", "%xmm1", "%xmm2", "%xmm3", "%xmm4"
            );
        }
    }
}

// new_array[i] = (array[i] + array[i+1] + array[i+2]) / 3
void section_d(int *array, int *new_array) {
    int num_3 = 3;
    for (int i = 0; i < SIZE - 2; ++i) {
        __asm__ __volatile__ (
        "movd       (%%rdx, %%rax,  4), %%xmm0;"    // load array[i]
        "cvtdq2ps  %%xmm0,  %%xmm0;"                // convert to float

        "movd      4(%%rdx, %%rax,  4), %%xmm1;"    // load array[i+1]
        "cvtdq2ps  %%xmm1,  %%xmm1;"                // ---

        "movd      8(%%rdx, %%rax,  4), %%xmm2;"    // load array[i+2]
        "cvtdq2ps  %%xmm2,  %%xmm2;"                // ---

        "vaddps    %%xmm0,  %%xmm1, %%xmm3;"        // add array[i] and array[i+1]
        "vaddps    %%xmm2,  %%xmm3, %%xmm0;"        // add array[i+2] to that

        "movd      %3,      %%xmm1;"                // load 3
        "cvtdq2ps  %%xmm1,  %%xmm1;"                // convert to float
        "vdivps    %%xmm1,  %%xmm0, %%xmm2;"        // divide sum by 3

        "cvtps2dq  %%xmm2,  %%xmm2;"                // convert result to int
        "movd      %%xmm2,  %0;"                    // store
        : "=m"(new_array[i])
        : "d"(array), "a"(i), "m"(num_3)
        : "%xmm0", "%xmm1", "%xmm2", "%xmm3"
        );
    }

    // second to last case
    __asm__ __volatile__ (
    "movd       (%%rdx, %%rax,  4), %%xmm0;"    // load array[i]
    "cvtdq2ps  %%xmm0,  %%xmm0;"                // convert to float

    "movd      4(%%rdx, %%rax,  4), %%xmm1;"    // load array[i+1]
    "cvtdq2ps  %%xmm1,  %%xmm1;"                // ---

    "movd      (%%rdx, %%rbx,  4), %%xmm2;"    // load array[i+2]
    "cvtdq2ps  %%xmm2,  %%xmm2;"                // ---

    "vaddps    %%xmm0,  %%xmm1, %%xmm3;"        // add array[i] and array[i+1]
    "vaddps    %%xmm2,  %%xmm3, %%xmm0;"        // add array[i+2] to that

    "movd      %3,      %%xmm1;"                // load 3
    "cvtdq2ps  %%xmm1,  %%xmm1;"                // convert to float
    "vdivps    %%xmm1,  %%xmm0, %%xmm2;"        // divide sum by 3

    "cvtps2dq  %%xmm2,  %%xmm2;"                // convert result to int
    "movd      %%xmm2,  %0;"                    // store
    : "=m"(new_array[SIZE-2])
    : "d"(array), "a"(SIZE-2), "m"(num_3), "b"(0)
    : "%xmm0", "%xmm1", "%xmm2", "%xmm3"
    );

    // last case
    __asm__ __volatile__ (
    "movd       (%%rdx, %%rax,  4), %%xmm0;"    // load array[i]
    "cvtdq2ps  %%xmm0,  %%xmm0;"                // convert to float

    "movd       (%%rdx, %%rbx,  4), %%xmm1;"    // load array[i+1]
    "cvtdq2ps  %%xmm1,  %%xmm1;"                // ---

    "movd      4(%%rdx, %%rbx,  4), %%xmm2;"    // load array[i+2]
    "cvtdq2ps  %%xmm2,  %%xmm2;"                // ---

    "vaddps    %%xmm0,  %%xmm1, %%xmm3;"        // add array[i] and array[i+1]
    "vaddps    %%xmm2,  %%xmm3, %%xmm0;"        // add array[i+2] to that

    "movd      %3,      %%xmm1;"                // load 3
    "cvtdq2ps  %%xmm1,  %%xmm1;"                // convert to float
    "vdivps    %%xmm1,  %%xmm0, %%xmm2;"        // divide sum by 3

    "cvtps2dq  %%xmm2,  %%xmm2;"                // convert result to int
    "movd      %%xmm2,  %0;"                    // store
    : "=m"(new_array[SIZE-1])
    : "d"(array), "a"(SIZE-1), "m"(num_3), "b"(0)
    : "%xmm0", "%xmm1", "%xmm2", "%xmm3"
    );
}

// new_array[i] = array[i] * ((255 / d / 2) * c) - array[i-1]
void section_e(int *array, int *new_array, int e, int f) {
    int num_2 = 2;
    int num_255 = 255;

    __asm__ __volatile__ (
    "movd     %4,     %%xmm0;"                  // load b
    "cvtdq2ps %%xmm0, %%xmm0;"                  // convert to float
    "movd     %7,     %%xmm1;"                  // load 255
    "cvtdq2ps %%xmm1, %%xmm1;"                  // convert to float
    "vdivps   %%xmm0, %%xmm1, %%xmm2;"          // divide 255 by b

    "movd     %6,     %%xmm0;"                  // load 2
    "cvtdq2ps %%xmm0, %%xmm0;"                  // convert to float
    "vdivps   %%xmm0, %%xmm2, %%xmm1;"          // divide result by 2

    "movd     %5,     %%xmm0;"                  // load c
    "cvtdq2ps %%xmm0, %%xmm0;"                  // convert to float
    "vmulps   %%xmm0, %%xmm1, %%xmm2;"          // multiply c with result

    "movd     (%%rdx, %%rax, 4), %%xmm0;"       // load array[i]
    "cvtdq2ps %%xmm0, %%xmm0;"                  // convert to float
    "vmulps   %%xmm0, %%xmm2, %%xmm1;"          // multiply c with result

    "movd     (%%rdx, %%rbx, 4), %%xmm0;"     // load array[i-1]
    "cvtdq2ps %%xmm0, %%xmm0;"                  // convert to float
    "vsubps   %%xmm0, %%xmm1, %%xmm2;"          // subtract array[i-1] from result

    "cvtps2dq %%xmm2, %%xmm2;"                  // convert to int
    "movd     %%xmm2, %0;"                      // store
    : "=m"(new_array[0])
    : "d"(array), "a"(0), "b"(SIZE-1), "m"(e), "m"(f), "m"(num_2), "m"(num_255)
    : "%xmm0", "%xmm1", "%xmm2"
    );

    for (int i = 1; i < SIZE; ++i) {
        __asm__ __volatile__ (
        "movd     %3,     %%xmm0;"                  // load b
        "cvtdq2ps %%xmm0, %%xmm0;"                  // convert to float
        "movd     %6,     %%xmm1;"                  // load 255
        "cvtdq2ps %%xmm1, %%xmm1;"                  // convert to float
        "vdivps   %%xmm0, %%xmm1, %%xmm2;"          // divide 255 by b

        "movd     %5,     %%xmm0;"                  // load 2
        "cvtdq2ps %%xmm0, %%xmm0;"                  // convert to float
        "vdivps   %%xmm0, %%xmm2, %%xmm1;"          // divide result by 2

        "movd     %4,     %%xmm0;"                  // load c
        "cvtdq2ps %%xmm0, %%xmm0;"                  // convert to float
        "vmulps   %%xmm0, %%xmm1, %%xmm2;"          // multiply c with result

        "movd     (%%rdx, %%rax, 4), %%xmm0;"       // load array[i]
        "cvtdq2ps %%xmm0, %%xmm0;"                  // convert to float
        "vmulps   %%xmm0, %%xmm2, %%xmm1;"          // multiply c with result

        "movd     -4(%%rdx, %%rax, 4), %%xmm0;"     // load array[i-1]
        "cvtdq2ps %%xmm0, %%xmm0;"                  // convert to float
        "vsubps   %%xmm0, %%xmm1, %%xmm2;"          // subtract array[i-1] from result

        "cvtps2dq %%xmm2, %%xmm2;"                  // convert to int
        "movd     %%xmm2, %0;"                      // store
        : "=m"(new_array[i])
        : "d"(array), "a"(i), "m"(e), "m"(f), "m"(num_2), "m"(num_255)
        : "%xmm0", "%xmm1", "%xmm2"
        );
    }
}

int main(int argc, char **argv) {
    //   m  d  a  s  c  d
    int a, x, b, m, e, f;
    int array_a[SIZE], array_b[SIZE], array_c[SIZE], array_d[SIZE], array_e[SIZE];
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

#include "iostream"

int func(int& a, int& b, int& result)
{
/*
    // AT&T/UNIX GCC Inline Assembly Sample
    static const char Argument[] =                   // C constants
        "some data";
    static const unsigned long Another_Argument =
        sizeof(Argument);
    long result;                                     // a C variable
    // x86, x86-64
    __asm__ __volatile__ (
        "op-code<length suffix> %%src_register, %%dest_register\n\t"
        "op-code<length suffix> $immediate, %%dest_register\n\t"
        // ...
        "op-code<length suffix> %<argument number>, %%dest_register\n\t"
        "op-code"
        : "=a" (result)                              // output argument/s
        : "D" ((unsigned long) file_descriptor),     // input arguments
            "S" (buffer),
            "d" (buffer_size),
            "r" (Argument), "r" (Another_Argument)
        : "%used register", "%another used register" // clobbered registers
    );
    //     result           : %<argument number> = %0
    //     file_descriptor  : ...                = %1
    //     buffer           :                    = %2
    //     buffer_size      :                    = %3
    //     Argument         :                    = %4
    //     Another_Argument :                    = %5
    //
    // The first quoted letter before the argument in brackets is a
    // register constraint. It tells the compiler to provide the
    // argument through that register.
    //
    // On X86/-64 the following register constraints are possible
    // +---+--------------------------+
    // | r :   any register           |
    // +---+--------------------------+
    // | a :   %rax, %eax, %ax, %al   |
    // | b :   %rbx, %ebx, %bx, %bl   |
    // | c :   %rcx, %ecx, %cx, %cl   |
    // | d :   %rdx, %edx, %dx, %dl   |
    // | S :   %rsi, %esi, %si        |
    // | D :   %rdi, %edi, %di        |
    // +---+--------------------------+
    //     register long result ("r7"); // 32-bit ARM
    //     register long result ("x0"); // 64-bit ARM
    // All registers used as input or output arguments should not be
    // listed as clobbered.
    //
    // https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html
*/
	__asm__ __volatile__
	(
		"movl %1, %%eax\n\t"
		"movl %2, %%edx\n\t"
		"imull %%edx, %%eax\n\t"
		"movl %%eax, %0"
		:"=a"(result):"b"(a), "c"(b)
	);
}


int main(int argc, char** argv)
{
	int a = 5;
	int b = 5;
	int c = 0;

	func(a, b, c);

	std::cout << "a * b = " << c << std::endl;

	double d = 5.0;
	double f = 120.0;

	float j = f / d;

	std::cout << "f / d = " << j << std::endl;

	return 0;
}

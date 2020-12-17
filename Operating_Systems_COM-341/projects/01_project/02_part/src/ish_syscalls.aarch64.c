// syscall numbers taken from https://github.com/torvalds/linux/blob/v4.17/include/uapi/asm-generic/unistd.h

// read input from a file or stdin
long ish_read(
        int file_descriptor,
        void *buffer,
        unsigned long buffer_size) {
    register long result asm("x0");
    __asm__ __volatile__ (
    "mov x8, #63\n\t"
    "svc #0"
    : "=r" (result)
    ::"x8"
    );
    return result;
}

// change the directory to path
int ish_chdir(const char *path) {
    register int result asm("w0");
    __asm__ __volatile__ (
    "mov x8, #49\n\t"
    "svc #0"
    : "=r" (result)
    ::"x8"
    );
    return result;
}

// exit from current program
void ish_exit(int status) {
    __asm__ __volatile__ (
    "mov x8, #93\n\t"
    "svc #0"
    :: : "x8"
    );
}

// stat a file to see if it is there
// use the value for AT_FDCWD from torvalds repo
// https://github.com/torvalds/linux/blob/acf25aa66371359f542d14e8d993b530fe25d7ac/tools/perf/tests/openat-syscall-tp-fields.c
// line 22
// use fstatat
int ish_stat(const char *path, void *stat_result) {
    register int result asm("w0");
    __asm__ __volatile__ (
    "mov x8, #79\n\t"
    "mov x3, #0\n\t"
    "mov x2, x1\n\t"
    "mov x1, x0\n\t"
    "mov x0, #-100\n\t"
    "svc #0"
    : "=r" (result)
    ::"x8", "x1", "x2", "x3"
    );
    return result;
}

// open a file -- get a file descriptor, openat
int ish_open(const char *path, int flags) {
    register int result asm("w0");
    __asm__ __volatile__ (
    "mov x8, #56\n\t"
    "mov x2, x1\n\t"
    "mov x1, x0\n\t"
    "mov x0, #-100\n\t"
    "svc #0"
    : "=r" (result)
    ::"x8", "x1", "x2"
    );
    return result;
}

// use openat with special arguments
// constants are form linux source code, in octal
int ish_creat(const char *path, unsigned int mode) {
    // WRONLY = 00001;
    // CREAT  = 00100;
    // TRUNC  = 01000;
    // ARG = WRONLY | CREAT | TRUNC = 01101 = 577;
    register int result asm("w0");
    __asm__ __volatile__ (
    "mov x8, #56\n\t"
    "mov x3, x1\n\t"
    "mov x2, #577 \n\t"
    "mov x1, x0\n\t"
    "mov x0, #-100\n\t"
    "svc #0"
    : "=r" (result)
    ::"x8", "x1", "x2", "x3"
    );
    return result;
}

// using dup3 with 0 arguments
int ish_dup2(int old_file_descriptor, int new_file_descriptor) {
    register int result asm("w0");
    __asm__ __volatile__ (
    "mov x8, #24\n\t"
    "mov x2, #0 \n\t"
    "svc #0"
    : "=r" (result)
    ::"x8", "x2"
    );
    return result;
}

int ish_close(int file_descriptor) {
    register int result asm("w0");
    __asm__ __volatile__ (
    "mov x8, #57\n\t"
    "svc #0"
    : "=r" (result)
    ::"x8"
    );
    return result;
}

// copied from disassembling fork in gdb
// uses close syscall
int ish_fork() {
    // flags:
    // CLONE_CHILD_CLEARTID 0x00200000
    // CLONE_CHILD_SETTID   0x01000000
    // SIGCHLD              0x00000011
    // code:                0x01200011
    //                      0x1200011
    register int result asm("w0");
    __asm__ __volatile__ (
    "mrs	x21, tpidr_el0\n\t"
    "sub	x5, x21, #0x700\n\t"        // 
    "mov	x0, #0x11 \n\t"             // prepare flags
    "add	x4, x5, #0xd0\n\t"          // 
    "movk	x0, #0x120, lsl #16\n\t"    // set appropriate flags
    "mov	x1, #0x0\n\t"               // no stack
    "mov	x2, #0x0\n\t"               // no parent tid
    "mov	x3, #0x0\n\t"               // no tls
    "mov	x8, #0xdc\n\t"              // code for syscall
    "svc #0"
    : "=r" (result)
    ::"x8", "x21", "x1", "x2", "x3", "x4", "x5"
    );
    return result;
}

// execve
int ish_execve(
        const char *path,
        char *const arguments[],
        char *const environment[]) {
    register int result asm("w0");
    __asm__ __volatile__ (
    "mov x8, #221\n\t"
    "svc #0"
    : "=r" (result)
    ::"x8"
    );
    return result;
}

// wait4
// we are missing the struct rusage *ru
// according to strace and gdb I can just put 0 into rusage
int ish_waitpid(int pid, int *status, int options) {
    register int result asm("w0");
    __asm__ __volatile__ (
    "mov x3, #0\n\t"
    "mov x8, #260\n\t"
    "svc #0"
    : "=r" (result)
    ::"x8", "x3"
    );
    return result;
}

// simple write call
long ish_write(
        int file_descriptor,
        const void *buffer,
        unsigned long buffer_size) {
    register long result asm("x0");
    __asm__ __volatile__ (
    "mov x8, #64\n\t"
    "svc #0"
    : "=r" (result)
    ::"x8"
    );
    return result;
}

// call numbers: https://github.com/westerndigitalcorporation/RISC-V-Linux/blob/master/linux/include/uapi/asm-generic/unistd.h
// resgisters: https://web.eecs.utk.edu/~smarz1/courses/ece356/notes/risc/imgs/regfile.png
// riscv specs: file:///tmp/mozilla_moritz0/riscv-spec-20191213.pdf
// numbers gotten through gdb disassembly

// read input from a file or stdin
// 63
// tested successfully
long ish_read(
        int file_descriptor,
        void *buffer,
        unsigned long buffer_size) {
    register long result asm("a0");
    __asm__ __volatile__ (
    "li a7, 63\n\t"
    "ecall"
    : "=r" (result)
    ::"a7"
    );
    return result;
}

// change the directory to path
// 49
// tested successfully
int ish_chdir(const char *path) {
    register int result asm("a0");
    __asm__ __volatile__ (
    "li a7, 49\n\t"
    "ecall"
    : "=r" (result)
    ::"a7"
    );
    return result;
}

// exit from current program
// 94
// tested successfully
void ish_exit(int status) {
    __asm__ __volatile__ (
    "li a7, 94\n\t"
    "ecall"
    :: : "a7"
    );
}

// stat a file to see if it is there
// 79
// third argument is zero
// AT_FDCWD is -100 again
// tested successfully
int ish_stat(const char *path, void *stat_result) {
    register int result asm("a0");
    __asm__ __volatile__ (
    "li a3, 0\n\t"
    "mv a2, a1\n\t"
    "mv a1, a0\n\t"
    "li a0, -100\n\t"
    "li a7, 79\n\t"
    "ecall"
    : "=r" (result)
    ::"a7", "a1", "a2", "a3"
    );
    return result;
}

// open a file -- get a file descriptor, openat
// 56
// AT_FDCWD is -100 again
// tested successfully
int ish_open(const char *path, int flags) {
    register int result asm("a0");
    __asm__ __volatile__ (
    "mv a2, a1\n\t"
    "mv a1, a0\n\t"
    "li a0, -100\n\t"
    "li a7, 56\n\t"
    "ecall"
    : "=r" (result)
    ::"a7", "a1", "a2"
    );
    return result;
}

// use openat with special arguments
// 56
// AT_FDCWD is -100 again
// constants are form linux source code, in octal
// tested successfully
int ish_creat(const char *path, unsigned int mode) {
    // openat(AT_FDCWD, "test", O_WRONLY|O_CREAT|O_TRUNC, 0644) = 3
    // WRONLY = 00001;
    // CREAT  = 00100;
    // TRUNC  = 01000;
    // ARG = WRONLY | CREAT | TRUNC = 01101 = 577;
    register int result asm("a0");
    __asm__ __volatile__ (
    "mv a3, a2\n\t"
    "li a2, 577\n\t"
    "mv a1, a0\n\t"
    "li a0, -100\n\t"
    "li a7, 56\n\t"
    "ecall"
    : "=r" (result)
    ::"a7", "a1", "a2", "a3"
    );
    return result;
}

// using dup3 with 0 arguments
// 24
// tested successfully
int ish_dup2(int old_file_descriptor, int new_file_descriptor) {
    register int result asm("a0");
    __asm__ __volatile__ (
    "li a2, 0\n\t"
    "li a7, 24\n\t"
    "ecall"
    : "=r" (result)
    ::"a7", "a2"
    );
    return result;
}

// 57
// tested successfully
int ish_close(int file_descriptor) {
    register int result asm("a0");
    __asm__ __volatile__ (
    "li a7, 57\n\t"
    "ecall"
    : "=r" (result)
    ::"a7"
    );
    return result;
}

// copied from disassembling fork in gdb
// 220
// uses clone syscall
// tested successfully
int ish_fork() {
    // flags:
    // CLONE_CHILD_CLEARTID 0x00200000
    // CLONE_CHILD_SETTID   0x01000000
    // SIGCHLD              0x00000011
    // code:                0x01200011
    //                      0x1200011
    // clone(child_stack=NULL, 
    // flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, 
    // child_tidptr=0x370ba0d0) = 1794
    //
    // gdb stuff:
    // 	addi	sp,sp,-48
    //  sd	s0,32(sp)
    // *lw	s0,-1808(tp)     <- tp = thread pointer
    //  sd	s1,24(sp)
    // *li	a0,0
    // *snez	s1,s0        <- set s1 zero if s0 == 0
    // *mv	a1,s1
    //  sd	ra,40(sp)
    // *sd	s2,16(sp)
    // *sd	s3,8(sp)
    //  jal	ra,0x3a30c <__run_fork_handlers>
    //  bnez	s0,0x21812 <fork+304>
    // *lui	a0,0x1200        <- simply a unsigned load
    // *li	a7,220           <- load syscall number
    // *addi	a0,a0,17     <- finish loading the constants
    //  li	a1,0
    //  li	a2,0
    //  li	a3,0
    //  addi	a4,tp,-1600 # 0xfffffffffffff9c0
    //  ecall
    //
    //  order of arguments:
    //  long clone(unsigned long flags, void *stack,
    //               int *parent_tid, unsigned long tls,
    //               int *child_tid);

    register int result asm("a0");
    __asm__ __volatile__ (
    "lui  a0, 0x1200\n\t"     // loads and sing extends a value to 32bit
    "addi a0, a0, 17\n\t"     // add to a0
    "li	  a1, 0\n\t"
    "li	  a2, 0\n\t"
    "li	  a3, 0\n\t"
    "addi a4, tp, -1600\n\t"  // get thread pointer / tid
    "li   a7, 220\n\t"
    "ecall"
    : "=r" (result)
    ::"a7", "a1", "a2", "a3", "a4"
    );
    return result;
}

// execve
// 221
// tested successfully
int ish_execve(
        const char *path,
        char *const arguments[],
        char *const environment[]) {
    register int result asm("a0");
    __asm__ __volatile__ (
    "li a7, 221\n\t"
    "ecall"
    : "=r" (result)
    ::"a7"
    );
    return result;
}

// wait4
// 260
// we are missing the struct rusage *ru
// according to strace and gdb I can just put 0 into rusage
int ish_waitpid(int pid, int *status, int options) {
    // wait4(2102, [{WIFEXITED(s) && WEXITSTATUS(s) == 0}], 0, NULL) = 2102
    register int result asm("a0");
    __asm__ __volatile__ (
    "li a7, 260\n\t"
    "li a3, 0\n\t"
    "ecall"
    : "=r" (result)
    ::"a7", "a3"
    );
    return result;
}

// simple write call
long ish_write(
        int file_descriptor,
        const void *buffer,
        unsigned long buffer_size) {
    register long result asm("a0");
    __asm__ __volatile__ (
    "li a7, 64\n\t"
    "ecall"
    : "=r" (result)
    ::"a7"
    );
    return result;
}

// call numbers: /usr/include/mips64el-linux-gnuabi64/asm/unistd_n64.h
// resgisters: http://www.cs.uwm.edu/classes/cs315/Bacon/Lecture/HTML/ch05s03.html
// + gdb disassembly

// read input from a file or stdin
// 5000
// tested successfully
long ish_read(
        int file_descriptor,
        void *buffer,
        unsigned long buffer_size) {
    register long result asm("v0");
    __asm__ __volatile__ (
    "li $v0, 5000\n\t"
    "syscall"
    : "=r" (result)
    );
    return result;
}

// change the directory to path
// 5078
// tested successfully
int ish_chdir(const char *path) {
    register int result asm("v0");
    __asm__ __volatile__ (
    "li $v0, 5078\n\t"
    "syscall"
    : "=r" (result)
    );
    return result;
}

// exit from current program (exit_group)
// 5205
// tested successfully
void ish_exit(int status) {
    __asm__ __volatile__ (
    "li $v0, 5205\n\t"
    "syscall"
    :: :"v0"
    );
}

// stat a file to see if it is there
// 5004
// tested successfully
int ish_stat(const char *path, void *stat_result) {
    register int result asm("v0");
    __asm__ __volatile__ (
    "li $v0, 5004\n\t"
    "syscall"
    : "=r" (result)
    );
    return result;
}

// open a file -- get a file descriptor, openat
// 5247
// AT_FDCWD is -100 again
// tested successfully
int ish_open(const char *path, int flags) {
    register int result asm("v0");
    __asm__ __volatile__ (
    "move $a2, $a1\n\t"
    "move $a1, $a0\n\t"
    "li   $a0, -100\n\t"
    "li   $v0, 5247\n\t"
    "syscall"
    : "=r" (result)
    ::"a0", "a1", "a2"
    );
    return result;
}

// use creat
// 5083
// tested successfully
int ish_creat(const char *path, unsigned int mode) {
    register int result asm("v0");
    __asm__ __volatile__ (
    "li $v0, 5083\n\t"
    "syscall"
    : "=r" (result)
    );
    return result;
}

// using dup3 with 0 arguments
// 5286
// tested successfully
int ish_dup2(int old_file_descriptor, int new_file_descriptor) {
    register int result asm("v0");
    __asm__ __volatile__ (
    "li $a2, 0\n\t"
    "li $v0, 5286\n\t"
    "syscall"
    : "=r" (result)
    ::"a2"
    );
    return result;
}

// 5003
// tested successfully
int ish_close(int file_descriptor) {
    register int result asm("v0");
    __asm__ __volatile__ (
    "li $v0, 5003\n\t"
    "syscall"
    : "=r" (result)
    );
    return result;
}

// copied from disassembling fork in gdb
// 5055
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
    // child_tidptr=0x1277ea0d0) = 401
    //
    // gdb:
    //    0x0000000120021380 <+0>:	daddiu	sp,sp,-80
    //    sd	gp,64(sp)
    //    lui	gp,0x9
    //    daddu	gp,gp,t9
    //    sd	ra,72(sp)
    //    sd	s6,56(sp)
    //    sd	s5,48(sp)
    //    sd	s4,40(sp)
    //    sd	s3,32(sp)
    //    sd	s2,24(sp)
    //    sd	s1,16(sp)
    //    sd	s0,8(sp)
    //    daddiu	gp,gp,-25360
    //    rdhwr	v1,$29
    //    lw	s0,-30480(v1)
    //    ld	s2,-30392(gp)
    //    sltu	s3,zero,s0
    //    move	a1,s3
    //    move	t9,s2
    //    jalr	t9
    //   *move	a0,zero
    //    bnez	s0,0x1200215e0 <fork+608>
    //   *ld	t9,-30384(gp)
    //   *rdhwr	v1,$29
    //   *lui	a0,0x120
    //   *daddiu	a0,a0,18
    //   *move	a1,zero
    //   *move	a2,zero
    //   *move	a3,zero
    //   *daddiu	a4,v1,-30272
    //   *li	v0,5055
    //   *syscall
    //
    //  order of arguments:
    //  long clone(unsigned long flags, void *stack,
    //               int *parent_tid, unsigned long tls,
    //               int *child_tid);

    register int result asm("v0");
    register int test asm("a4");
    __asm__ __volatile__ (
    "rdhwr  $v1, $29\n\t"         // get child tid
    "daddiu	$8, $v1, -30272\n\t" // move tid into place
    "lui	$a0, 0x120\n\t"       // get first part of flags
    "daddiu	$a0, $a0, 18\n\t"     // get second part of flags
    "li	    $a1, 0\n\t"
    "li	    $a2, 0\n\t"
    "li	    $a3, 0\n\t"
    "li     $v0, 5055\n\t"
    "syscall"
    : "=r" (result)
    // for some reason gcc wont let me put a4 here so I use 8 (same register)
    ::"a0", "a1", "a2", "a3", "8", "v1"
    );
    return result;
}

// execve
// 5057
// tested successfully
int ish_execve(
        const char *path,
        char *const arguments[],
        char *const environment[]) {
    register int result asm("v0");
    __asm__ __volatile__ (
    "li $v0, 5057\n\t"
    "syscall"
    : "=r" (result)
    );
    return result;
}

// wait4
// 5059
// we are missing the struct rusage *ru
// according to strace and gdb I can just put 0 into rusage
int ish_waitpid(int pid, int *status, int options) {
    register int result asm("v0");
    __asm__ __volatile__ (
    "li $a3, 0\n\t"
    "li $v0, 5059\n\t"
    "syscall"
    : "=r" (result)
    ::"a3"
    );
    return result;
}

// simple write call
// 5001
long ish_write(
        int file_descriptor,
        const void *buffer,
        unsigned long buffer_size) {
    register long result asm("v0");
    __asm__ __volatile__ (
    "li $v0, 5001\n\t"
    "syscall"
    : "=r" (result)
    );
    return result;
}

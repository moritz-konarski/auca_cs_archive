/*
 * This code has been copied from my project 1 part 2 solution for amd64
 */

#include "syscalls.h"

void exit(int status) {
    __asm__ __volatile__ (
    "mov $60, %%rax\n\t"
    "syscall"
    :: : "rax"
    );
}

int stat(const char *path, void *stat_result) {
    int result;
    __asm__ __volatile__ (
    "mov $4, %%rax\n\t"
    "syscall"
    : "=a" (result)
    );
    return result;
}

int fork() {
    int result;
    __asm__ __volatile__ (
    "mov $57, %%rax\n\t"
    "syscall"
    : "=a" (result)
    );
    return result;
}

int execve(
        const char *path,
        char *const arguments[],
        char *const environment[]) {
    int result;
    __asm__ __volatile__ (
    "mov $59, %%rax\n\t"
    "syscall"
    : "=a" (result)
    );
    return result;
}

int waitpid(int pid, int *status, int options) {
    int result;
    __asm__ __volatile__ (
    "mov $61, %%rax\n\t"
    "mov $0, %%r10\n\t"
    "syscall"
    : "=a" (result)
    ::"r10"
    );
    return result;
}

long write(
        int file_descriptor,
        const void *buffer,
        unsigned long buffer_size) {
    long result;
    __asm__ __volatile__ (
    "mov $1, %%rax\n\t"
    "syscall"
    : "=a" (result)
    );
    return result;
}

long read(
        int file_descriptor,
        void *buffer,
        unsigned long buffer_size) {
    long result;
    __asm__ __volatile__ (
    "mov $0, %%rax\n\t"
    "syscall"
    : "=a" (result)
    );
    return result;
}

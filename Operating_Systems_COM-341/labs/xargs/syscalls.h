/*
 * Much of this code has been copied from my project 1 part 2 solution for amd64
 */

#ifndef SYSCALLS
#define SYSCALLS

void exit(int status);

int stat(const char *path, void *stat_result);

int fork();

int execve(
        const char *path,
        char *const arguments[],
        char *const environment[]);

int waitpid(int pid, int *status, int options);

long write(
        int file_descriptor,
        const void *buffer,
        unsigned long buffer_size);

long read(
        int file_descriptor,
        void *buffer,
        unsigned long buffer_size);

#endif

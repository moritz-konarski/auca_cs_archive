# Project 1

## Requirements

1. [x] install `qemu`
2. [x] download the appropriate `iso`s or installers
3. [x] use provided scripts to download and install
4. [x] use the `First Last` as name, `last-f` as username
5. [x] password should be the same as the username

## Part 1

Until next Monday 23:00
1. [x] install Debian amd64 in QEMU 
2. [x] install Debian aarch64 in QEMU 
3. [x] Download and start mis64el Debian distro in QEMU 
4. [x] Download and start riscv64 Debian distro in QEMU
5. [x] get the output of `dmesg` from each os and also supply `/etc/shadow` and 
push it to github

## Part 2

- put source folder onto our machine
- instead of the library types use
```C
    typedef size_t   unisgned long;
    typedef ssize_t  long;
    typedef size_t   int;
```
- write the syscalls for the 4 architectures
    - `read`
    - `chdir`
    - `exit`
    - `stat`
    - `open`
    - `creat`
    - `dup2`
    - `close`
    - `fork`
    - `execve`
    - `waitpid`
    - `write`
- implement
    - `ish_read`
    - `ish_chdir`
    - `ish_exit`
    - `ish_stat`
    - `ish_open`
    - `ish_creat`
    - `ish_dup2`
    - `ish_close`
    - `ish_fork`
    - `ish_execve`
    - `ish_waitpid`
    - `ish_write`
- Test each custom system call function by replacing a related standard library
call in `ish.c` with a call to your new implementation. When everything is   
ready and works as expected, return the old system call names in `ish.c` and 
remove the `-D ISH_USE_STDLIB` preprocessor definition from the project's    
Makefile. Your shell will use the new calls after that. You can always switch
back by adding the definition back
- [ ] write the `ish_sycalls` for 
    - [x] `amd64`
        - [x] test syscalls on amd64 debian
    - [ ] `arm64`
        - stat -> fstatat
        - open -> openat
        - creat -> openat (special flags
        - dup2 -> dup3
        - wait -> wait4
    - [ ] `mips64el`
    - [ ] `riscv64`
- [ ] take notes on each syscall in C file
- [ ] make list of commands that test each syscall
- [ ] submit the files to github as `ish_syscalls.<arch>.c`

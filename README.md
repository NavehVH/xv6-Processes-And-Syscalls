# xv6-riscv — Assignment 1: Processes and Scheduling

This repository contains my implementation of Assignment 1 for the Operating Systems course (Spring 2025), based on the MIT xv6-riscv teaching operating system. The assignment focused on system calls, process management, and parallel computation using system-level constructs.

## Overview

The assignment consists of four tasks:

### Task 1: Hello World
- Wrote a simple userspace program (`helloworld.c`) that prints a message inside the xv6 shell.
- Modified the Makefile to include the new program and verified proper compilation and execution.

### Task 2: `memsize` System Call
- Implemented a custom system call `memsize()` to return the current process’s memory size in bytes.
- Created a userspace program (`memsize_test.c`) to demonstrate memory growth using `malloc()` and the effect of `free()`.

### Task 3: Exit Messages via `exit()` and `wait()`
- Extended the existing `exit()` and `wait()` system calls to support string-based exit messages.
- Modified the `proc` structure to include an `exit_msg[32]` field.
- Implemented safe user-to-kernel and kernel-to-user string copying using `argstr()` and `copyout()`.
- Updated `sh.c` so that the shell prints the exit message of child processes upon termination.
- Added a test program (`goodbye.c`) that exits with a message.

### Task 4: Parallel Work with `forkn()` and `waitall()`
- Implemented two new system calls:
  - `forkn(int n, int* pids)` — creates `n` child processes and returns their PIDs to the parent.
  - `waitall(int* n, int* statuses)` — blocks the caller until all of its child processes have exited, collecting their exit statuses.
- Ensured safe and atomic creation of multiple children, including cleanup logic on partial failure.
- Developed `bigarray.c`, a program that splits an array of integers across child processes, each computing a partial sum, and combines the results in the parent.

## Implementation Notes

- All code was implemented within a single modified copy of the xv6-riscv kernel as required.
- Proper process synchronization was ensured using `wait_lock` and per-process `p->lock`.
- Used `copyout()` and `argstr()` to safely transfer data between user space and kernel space.
- Zombie processes are correctly handled using `wait()` and `waitall()`, and `reparent()` ensures orphaned children are assigned to `initproc`.

## Building and Running

To build and launch xv6:

```bash
make clean
make qemu
```

## Modified Files

```bash
kernel/sysproc.c
kernel/syscall.c
kernel/proc.c

user/helloworld.c
user/memsize_test.c
user/goodbye.c
user/bigarray.c

user/user.h
user/usys.pl
Makefile
sh.c
```



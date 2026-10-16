# Week 1 - Topic Notes

## 1. Program and process

A program is a set of instructions saved in a file. A process is a program
that is currently running. Running the same program twice creates separate
processes.

- **PID:** Process ID. It identifies a process.
- **PPID:** Parent Process ID. It identifies the process that created it.
- **Parent:** The process that creates a child.
- **Child:** The new process created by the parent.

`getpid()` gives the current process's PID. `getppid()` gives its parent's PID.
PID values can be different every time we run the program.

## 2. Creating a child using fork()

`fork()` creates a child process. Both parent and child continue from the
statement after `fork()`, but they get different return values.

| Return value | Meaning |
| --- | --- |
| Less than 0 | Process creation failed |
| 0 | We are in the child process |
| Greater than 0 | We are in the parent; the value is the child's PID |

Basic pattern:

```c
pid_t pid = fork();

if (pid < 0) {
    perror("fork");
}
else if (pid == 0) {
    printf("Child Process\n");
}
else {
    printf("Parent Process\n");
}
```

`pid_t` is the type used for process IDs. `perror()` prints an error message.
The operating system decides which process runs first, so output order can vary.

The child starts with copies of the parent's ordinary variables. Changing a
variable in the child does not change the parent's copy.

## 3. Waiting for a child

`wait()` collects a child's termination information. If no child has finished
yet, it makes the parent wait for one to finish.

```c
wait(NULL);
printf("Child has finished\n");
```

`NULL` means we do not need to store the exit status. A parent with three
children normally calls `wait()` three times to collect all three.

## 4. Exit status

An exit status is a small number returned when a process ends. Usually,
0 means success and a nonzero value indicates another result or an error.

In the homework, the child calls `exit(10)`. The parent reads the result:

```c
int status;
wait(&status);

if (WIFEXITED(status)) {
    printf("Exit status = %d\n", WEXITSTATUS(status));
}
```

- `WIFEXITED(status)` checks whether the child ended normally.
- `WEXITSTATUS(status)` extracts its exit code.
- The value stored in `status` contains extra information; do not print it
  directly and assume it is the exit code.

## 5. Three children and a grandchild

When creating three children in a loop, each child must stop after doing its
work. Otherwise, it also continues the loop and creates more processes.

When a child calls `fork()`, the new process is a **grandchild of the original
parent**. In Classwork Q5, the original parent finds the natural-number sum,
the first child prints Fibonacci numbers, and the grandchild finds the factorial.

## 6. Orphan and zombie processes

| Orphan | Zombie |
| --- | --- |
| Child is still running, but its parent has exited | Child has exited, but its status has not been collected |
| Another process adopts it | A small process-table entry remains |
| Its PPID changes | Its state appears as `Z` in `ps` |

The orphan example uses `sleep()` so we can observe the PPID before and after
the parent exits. The adopting process is not necessarily PID 1.

The zombie example makes the parent sleep before calling `wait()`. While it
sleeps, open another terminal and run `ps -l`. Look for the child's PID and
the state `Z`. Calling `wait()` collects the child's status and removes its
zombie entry.

`sleep()` pauses for a number of seconds. It does not wait for a particular
process to finish; `wait()` does that for a child.

## 7. Running another program using exec()

An exec-family function replaces the current process's program. It does not
create another process. The PID stays the same.

```c
execlp("date", "date", (char *)NULL);
```

Here, the first `"date"` is the command to find in `PATH`. The second is the
program's first argument, and `NULL` ends the argument list. Successful exec
does not return to the old code. Code after this call runs only if it fails.

Homework Q6 follows: parent calls `fork()`, child runs `date` using `execlp()`,
and parent calls `wait()`.

## 8. Headers and a useful point

| Header | Used for |
| --- | --- |
| `stdio.h` | `printf()`, `scanf()`, `perror()` |
| `unistd.h` | `fork()`, `getpid()`, `getppid()`, `sleep()`, `execlp()` |
| `sys/wait.h` | `wait()` and exit-status macros |
| `stdlib.h` | `exit()` |

Output waiting in the `printf()` buffer can be copied during `fork()`. Calling
`fflush(stdout)` before forking clears pending output and helps avoid repeated
text, especially when output is redirected.

## 9. Quick viva revision

- **How many processes exist after one successful fork?** Two, if both are
  still running: one parent and one child.
- **Does fork return the same value in both?** No. Child gets 0; parent gets
  the child's PID.
- **Why use wait?** To wait for and collect a child's termination information.
- **Does exec create a child?** No. It replaces the current program.
- **Can parent and child print in any order?** Yes, unless the program adds
  synchronization to control the relevant steps.

## 10. Questions covered

- Classwork Q1-Q3: PID, PPID, identifying processes, and waiting.
- Classwork Q4-Q5: Different calculations in parent, child, and grandchild.
- Homework Q1-Q2: Even/odd numbers and three child processes.
- Homework Q3-Q6: Exit status, orphan, zombie, and executing a command.

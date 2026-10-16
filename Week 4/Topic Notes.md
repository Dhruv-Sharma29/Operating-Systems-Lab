# Week 4 - Topic Notes

## 1. Topics for this week

- Inter-process communication using a pipe.
- Calculating an array sum in the parent and checking it in the child.
- Creating, writing, and reading a text file.
- Understanding the order of work between processes.

## 2. Why a pipe is needed in Q1

Parent and child have separate copies of ordinary variables after `fork()`.
If the parent calculates `sum` after forking, its update does not automatically
appear in the child's copy.

**IPC** means inter-process communication. A pipe is one way to send data
between processes. The current Q1 uses it to send the parent's sum to the child.

## 3. Pipe basics

```c
int pipefd[2];
pipe(pipefd);
```

| End | Purpose |
| --- | --- |
| `pipefd[0]` | Read data |
| `pipefd[1]` | Write data |

Create the pipe **before** `fork()` so both processes inherit its file
descriptors. A file descriptor is an integer used to identify an open input
or output resource.

Parent's part:

```c
close(pipefd[0]);
write(pipefd[1], &sum, sizeof(sum));
close(pipefd[1]);
```

Child's part:

```c
close(pipefd[1]);
read(pipefd[0], &sum, sizeof(sum));
close(pipefd[0]);
```

- `&sum` gives the address of the integer to send or receive.
- `sizeof(sum)` gives the number of bytes occupied by it.
- Close the end that a process does not use, and close the other end after use.
- For this one-way transfer, the parent writes and the child reads.
- A blocking `read()` on an empty pipe waits while a writer still has it open.
- In a more complete program, check the return values of `pipe()`, `read()`,
  and `write()` to confirm they succeeded and transferred the expected bytes.

Q1 follows this order: read the array, create a pipe, fork, calculate the sum
in the parent, send it, receive it in the child, and check primality.

For the array `{2, 3, 6}`, the parent sends 11 and the child reports it as prime.

## 4. File handling in C

`FILE *` is used with C's file-handling functions.

```c
FILE *file;
file = fopen("input.txt", "w");
```

| Mode | Meaning |
| --- | --- |
| `"w"` | Write; create the file or replace its old contents |
| `"r"` | Read an existing file |
| `"a"` | Append at the end; create the file if necessary |

If `fopen()` fails, it returns `NULL`. Always check before using the pointer.

## 5. Writing and reading the file

The parent writes the name, university roll number, and class using `fprintf()`.
It works like `printf()`, but sends output to a file.

```c
fprintf(file, "Class: CSE-A\n");
fclose(file);
```

`fclose()` flushes buffered output and closes the file. The current program
has sample details in its `fprintf()` statements; replace those details with
your own when using it for your lab work.

The child opens the same file using `"r"` and reads one character at a time.
The basic reading pattern is:

```c
int ch;
while ((ch = fgetc(file)) != EOF) {
    printf("%c", ch);
}
```

`EOF` marks the end of input. Use `int` for `fgetc()`'s result so it can hold
both a character value and `EOF`. The current example declares `ch` as `char`;
the `int` pattern above is the correct general form.

`input.txt` is created in the directory from which the program runs.

## 6. Order of work in Q2

The parent and child are created first. The parent then writes the file and
closes it. The child uses `sleep(1)` before opening the file to give the parent
time to write it. The parent calls `wait(NULL)` before ending.

A sleep is a delay, so it does not guarantee that the parent has finished
writing. Writing and closing the file before `fork()`, or sending a completion
signal through a pipe, provides a reliable way to order these steps.

`wait()` at the end makes the parent wait for the child; it does not make
the child wait for the parent's file write.

## 7. Quick viva revision

- **What is IPC?** Communication between processes.
- **Which pipe end reads?** `pipefd[0]`.
- **Why create the pipe before fork?** So parent and child inherit its ends.
- **Why use sizeof(sum)?** To transfer the number of bytes used by `sum`.
- **Does write mode preserve old file contents?** No, `"w"` replaces them.
- **What does fopen return on failure?** `NULL`.
- **Why close the file after writing?** To flush output and release the file.
- **Why store fgetc's result in int?** To distinguish all character values
  from `EOF`.

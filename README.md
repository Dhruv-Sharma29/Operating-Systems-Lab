# OS Lab - Semester 5

Each C file starts with its question, followed by a simple standalone solution.
The programs use basic loops, if/else statements, and short variable names.
The folders use week numbers. Question numbers restart for each section.

| Week | Section | Questions |
| --- | --- | --- |
| Week 1 | Classwork | 5 |
| Week 1 | Homework | 6 |
| Week 2 | Classwork | 2 |
| Week 3 | Classwork | 2 |
| Week 4 | Classwork | 2 |
| Week 5 | Classwork | 1 (Writer & Reader) |

## Compile and run

Use Linux or macOS with GCC or Clang. These programs use Unix process
functions such as `fork()`, `wait()`, `execlp()`, and `mkfifo()`.

For example, from this folder:

```sh
cd "Week 1/Classwork"
gcc -std=c11 -Wall -Wextra Q1_pid_ppid.c -o q1
./q1
```

Compile each C file separately, changing the source name and executable name
for the question you want to run.

For named pipes (Week 5 FIFO), compile both writer and reader and run them in separate terminals:

```sh
# Terminal 1:
cd "Week 5/Classwork"
gcc -std=c11 -Wall -Wextra Q1_fifo_writer.c -o writer
./writer

# Terminal 2:
cd "Week 5/Classwork"
gcc -std=c11 -Wall -Wextra Q1_fifo_reader.c -o reader
./reader
```

## Topic notes

Each week has beginner-friendly explanations, examples, and quick viva revision.

| Week | Notes |
| --- | --- |
| Week 1 | [Processes, fork, wait, orphan, zombie, and exec](Week%201/Topic%20Notes.md) |
| Week 2 | [Prime numbers, factorial, Fibonacci, and Armstrong numbers](Week%202/Topic%20Notes.md) |
| Week 3 | [Arrays, strings, recursion, and permutations](Week%203/Topic%20Notes.md) |
| Week 4 | [Pipes, IPC, and file handling](Week%204/Topic%20Notes.md) |
| Week 5 | [Named pipes (FIFO), mkfifo, and IPC between processes](Week%205/Topic%20Notes.md) |

## Practice notes

- The current Fibonacci programs print the first `n` terms.
- Use small inputs for calculations. For the usual 32-bit `int` factorial in
  Week 2, use 0 through 12; Week 1's `long long` factorial fits 0 through 20.
- The Armstrong example uses cubes of digits. The Week 2 notes explain how this
  differs from the general definition.
- Arrays have room for 100 elements. Use a short word such as `abc` for
  permutations; repeated letters may produce repeated lines.
- PID values and process output order can change between runs.
- For the zombie example, run `ps -l` in another terminal during the parent's
  10-second sleep and look for the child's PID with state `Z`.
- Week 4 Q1 transfers the parent's array sum through a pipe.
- Week 4 Q2 writes sample details to `input.txt` in the directory from which
  it runs. Replace the sample details in its `fprintf()` lines with your own.
- Week 5 Q1 demonstrates IPC using a named pipe (`myfifo`). Run the writer and
  reader in separate terminals so the writer passes the input message to the reader.

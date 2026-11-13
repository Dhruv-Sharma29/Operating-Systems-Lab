# OS Lab - Semester 5

Solutions for the Operating Systems Laboratory (B.Tech CSE, Graphic Era).
Each C file starts with a comment stating its question, followed by a simple
standalone solution using basic loops, `if`/`else`, and short variable names.
Folders are named by week; question numbers restart in each section.

## Index

| Week | Topic | Programs | Notes |
| --- | --- | --- | --- |
| Week 1 | Process creation: `fork`, `wait`, orphan, zombie, `exec` | 5 classwork, 6 homework | [notes](Week%201/Topic%20Notes.md) |
| Week 2 | Prime, factorial, Fibonacci, Armstrong with `fork` | 2 classwork | [notes](Week%202/Topic%20Notes.md) |
| Week 3 | Arrays, strings, recursion, permutations | 2 classwork | [notes](Week%203/Topic%20Notes.md) |
| Week 4 | Unnamed pipe and file handling | 2 classwork | [notes](Week%204/Topic%20Notes.md) |
| Week 5 | Named pipe (FIFO) | 1 (writer + reader) | [notes](Week%205/Topic%20Notes.md) |
| Week 6 | Shared memory and message queue | 2 (each a pair) | [notes](Week%206/Topic%20Notes.md) |
| Week 7 | CPU scheduling and page replacement | 5 classwork | [notes](Week%207/Topic%20Notes.md) |

The notes for each week give beginner-friendly explanations, worked examples,
and quick viva revision.

## Compile and run

Use Linux or macOS with GCC or Clang. The programs use Unix system calls such
as `fork()`, `wait()`, `execlp()`, `mkfifo()`, `shmget()`, and `msgget()`.

Compile each file on its own, changing the source and executable names:

```sh
cd "Week 1/Classwork"
gcc -std=c11 -Wall -Wextra Q1_pid_ppid.c -o q1
./q1
```

### Two-process programs

Some experiments come as a pair of programs that talk to each other.

**Week 5 (FIFO)** — run the two sides in separate terminals:

```sh
cd "Week 5/Classwork"
gcc -std=c11 -Wall -Wextra Q1_fifo_writer.c -o writer
gcc -std=c11 -Wall -Wextra Q1_fifo_reader.c -o reader
# terminal 1: ./writer      terminal 2: ./reader
```

**Week 6 (shared memory, message queue)** — run the writer/sender first, then
the reader/receiver, from the same folder so `ftok(".", ...)` gives both the
same key:

```sh
cd "Week 6/Classwork"
gcc -std=c11 -Wall -Wextra Q1_shm_writer.c -o writer
gcc -std=c11 -Wall -Wextra Q1_shm_reader.c -o reader
./writer      # Enter data: ...
./reader      # Data received: ...
```

The reader/receiver removes the IPC resource when it finishes. List any that
are left over with `ipcs -m` (shared memory) or `ipcs -q` (message queues),
and remove one by id with `ipcrm -m <id>` or `ipcrm -q <id>`.

## Practice notes

- Fibonacci programs print the first `n` terms.
- Use small inputs for calculations. For the 32-bit `int` factorial in Week 2,
  use 0 through 12; Week 1's `long long` factorial fits 0 through 20.
- The Armstrong example uses cubes of digits. The Week 2 notes explain how this
  differs from the general definition.
- Arrays hold up to 100 elements. Use a short word such as `abc` for
  permutations; repeated letters may produce repeated lines.
- PID values and the order of parent/child output can change between runs.
- For the zombie example, run `ps -l` in another terminal during the parent's
  10-second sleep and look for the child's PID with state `Z`.
- Week 4 Q2 writes sample details to `input.txt` in the folder it runs from.
  Replace the sample details in its `fprintf()` lines with your own.
- Week 7 scheduling programs assume all processes arrive at time 0. Try
  P1 = 24, P2 = 3, P3 = 3: FCFS average waiting time is 17.00 and SJF is 3.00.
  Trace one scheduling table and one FIFO/LRU frame sequence by hand before the
  viva — examiners usually ask for it.

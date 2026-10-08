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

## Compile and run

Use Linux or macOS with GCC or Clang. These programs use Unix process
functions such as `fork()`, `wait()`, and `execlp()`.

For example, from this folder:

```sh
cd "Week 1/Classwork"
gcc -std=c11 -Wall -Wextra Q1_pid_ppid.c -o q1
./q1
```

Compile each C file separately, changing the source name and executable name
for the question you want to run.

## Notes

- Fibonacci "up to n" means values no greater than n in these solutions.
- Factorial inputs are limited to 0 through 20 so the result fits in an
  `unsigned long long`.
- Week 3 Question 1 calculates the array sum and checks primality in the child.
  Week 4 Question 1 calculates the sum in the parent and checks it in the child.
- The permutation program reads a word of up to 8 characters and prints each
  permutation using recursion. Repeated letters may give repeated results.
- PID values change each time a program runs. The three children may print in
  a different order on different runs.
- The orphan example uses short sleeps to let you see the PPID change. Its final
  PPID belongs to the process that adopts it and is not necessarily 1.
- For the zombie example, run the printed `ps` command in another terminal during
  the parent's 10-second sleep. `Z` in the state column indicates a zombie.
- The command-execution homework runs `date` because that is the lab question.
- Week 4's file program asks for your details and creates `input.txt` in the
  directory from which you run it. Running it again replaces that file.

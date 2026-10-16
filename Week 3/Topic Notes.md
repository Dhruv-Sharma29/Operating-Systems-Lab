# Week 3 - Topic Notes

## 1. Topics for this week

- Arrays and their sum inside a child process.
- Checking whether the sum is prime.
- Reading a string inside a child process.
- Printing permutations using recursion and backtracking.

## 2. Arrays and their sum

An array stores several values of the same type. Its index starts at 0.

```c
int arr[100];
```

This array can hold 100 integers, at indexes 0 through 99. If the user enters
`n` elements, use indexes 0 through `n - 1`. For this program, choose `n`
from 1 to 100.

```c
sum = 0;
for (int i = 0; i < n; i++) {
    sum = sum + arr[i];
}
```

For `{2, 3, 6}`, the sum is 11, which is prime. For `{2, 3, 5}`, the sum is
10, which is not prime. A sum of 1 or less is not prime.

## 3. Work done by the child

In Q1, the array is read before `fork()`. The child inherits its values.
Inside the `pid == 0` branch, it calculates the sum and checks primality.

The parent's ordinary variables do not automatically receive the child's
changes. Both calculations can use the same `sum` here because they happen
in the same child process. Week 4 shows how a pipe can transfer a value
between processes.

The current Week 3 parent does not call `wait()`. It may finish before the
child finishes its work.

## 4. Strings in C

A C string is a character array ending with the null character `\0`.

```c
char str[20];
```

This has room for 19 characters and the terminating `\0`.
`strlen(str)` counts the characters before `\0`; it does not count `\0` itself.

`scanf("%s", str)` reads one word and stops at whitespace. A width such as
`scanf("%19s", str)` keeps the input within a 20-character array. The current
example uses `%s`, so practise with a short word such as `abc`.

In Q2, input is read inside the child after `fork()`.

## 5. Permutations

A permutation is an arrangement of characters in a different order.
For `abc`, the six arrangements are:

```text
abc  acb  bac  bca  cab  cba
```

With `n` different characters, there are `n!` permutations:
3 characters give 6; 4 give 24; 5 give 120. Output grows quickly, so short
strings are easier to practise with. Repeated letters can produce repeated
lines in this simple program.

## 6. Recursion and backtracking

**Recursion** means a function calls itself with a smaller problem.
**Backtracking** means undoing a choice before trying another choice.

The program uses `permute(str, left, right)`:

1. Choose a character for position `left` by swapping it into that position.
2. Call `permute(str, left + 1, right)` for the remaining positions.
3. Swap the characters back before trying the next choice.
4. When `left == right`, one arrangement is complete, so print it.

`left == right` is the **base case**. It stops further recursion on that branch.
Swapping back restores the string for the next branch.

## 7. Quick viva revision

- **Where does an array's first element start?** At index 0.
- **Why set sum to 0?** It is the starting value for addition.
- **Does changing sum in the child change it in the parent?** No.
- **What ends a C string?** The null character `\0`.
- **What does strlen return?** The string length without `\0`.
- **Why swap back in the permutation program?** To restore the string before
  trying another arrangement.
- **How many permutations does a word with four distinct letters have?**
  `4! = 24`.

# Week 2 - Topic Notes

## 1. Different work in parent and child

After `fork()`, use its return value to divide the work:

| Question | Child process | Parent process |
| --- | --- | --- |
| Q1 | Check whether a number is prime | Find its factorial |
| Q2 | Call the Fibonacci function | Call the Armstrong function |

The current Week 2 programs do not call `wait()`. Parent and child can work
independently, and their output may appear in different orders.

## 2. Prime numbers

A prime number is greater than 1 and has exactly two positive factors:
1 and itself.

- 2, 3, 5, 7, and 11 are prime.
- 4 is not prime because it is divisible by 2.
- 0, 1, and negative numbers are not prime.

Start with `isPrime = 1`. Set it to 0 if the number is at most 1 or if a divisor
is found. `break` stops the loop once a divisor is found.

```c
for (int i = 2; i * i <= num; i++) {
    if (num % i == 0) {
        isPrime = 0;
        break;
    }
}
```

`%` gives the remainder. A remainder of 0 means the number is divisible by `i`.
Checking up to the square root is enough: a factor larger than the square root
has a matching factor smaller than it.

## 3. Factorial

The factorial of a nonnegative integer is the product of all integers from
1 to that number.

```text
5! = 1 x 2 x 3 x 4 x 5 = 120
0! = 1
```

```c
int factorial = 1;
for (int i = 1; i <= num; i++) {
    factorial = factorial * i;
}
```

Start with 1. Starting with 0 would make every multiplication give 0.
Factorials grow quickly. For the current Week 2 program's usual 32-bit `int`,
use inputs from 0 to 12 so the factorial fits. Week 1 uses `long long` for
factorial, which can hold results through 20! on the lab's usual systems.

## 4. Fibonacci series

Start with 0 and 1. Each next number is the sum of the previous two.

```text
0 1 1 2 3 5 8 13 ...
```

The update is:

```c
next = a + b;
a = b;
b = next;
```

The current programs use `n` as the **number of terms**. For `n = 5`, the
Fibonacci output is `0 1 1 2 3`. Large inputs can overflow the `int` variables,
so use small values when practising.

## 5. Armstrong numbers

In general, an Armstrong number equals the sum of its digits, each raised
to the number of digits. For a three-digit number, we use cubes.

```text
153 = 1^3 + 5^3 + 3^3
    = 1 + 125 + 27
    = 153
```

The current beginner program always uses cubes:

```c
digit = temp % 10;
sum = sum + digit * digit * digit;
temp = temp / 10;
```

- `% 10` extracts the last digit.
- Integer division by 10 removes the last digit.
- `temp` is a copy, so the original number remains available for comparison.

For `n = 500`, this program prints `1 153 370 371 407`. It starts checking at 1.
Its fixed-cube method does not implement the general definition for every
digit count. For example, 1634 needs fourth powers.

## 6. Functions

A function groups statements that perform one task. It makes the main program
easier to follow.

```c
void fibonacci(int n);
void armstrong(int n);
```

`n` is the input parameter. `void` means these functions do not return a value;
they print the result themselves. In Q2, Fibonacci uses `n` as a term count,
while Armstrong checks numbers up to `n`.

## 7. Quick viva revision

- **Is 1 prime?** No, it has only one positive factor.
- **What is 0!?** 1.
- **Why use a temporary variable for digits?** Extracting digits changes it;
  we still need the original number for comparison.
- **Why start factorial at 1?** 1 is the starting value for multiplication.
- **Why use functions?** To keep a task together and make code easier to reuse.

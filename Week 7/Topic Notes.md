# Week 7 - Topic Notes

## 1. Topics for this week

- CPU scheduling: FCFS, SJF (non-preemptive), and Priority (non-preemptive).
- Calculating waiting time (WT) and turnaround time (TAT).
- Page replacement: FIFO and LRU.
- Counting page faults and page hits.

## 2. Scheduling terms

| Term | Meaning |
| --- | --- |
| Burst Time (BT) | CPU time a process needs |
| Arrival Time (AT) | Time the process enters the ready queue |
| Completion Time (CT) | Time the process finishes |
| Turnaround Time (TAT) | `CT - AT`, total time from arrival to finish |
| Waiting Time (WT) | `TAT - BT`, time spent waiting in the ready queue |

In these programs, **all processes arrive at time 0**, so:

```c
wt[0] = 0;
wt[i] = wt[i - 1] + bt[i - 1];   // wait for everyone before you
tat[i] = wt[i] + bt[i];
```

The only difference between the three algorithms is the **order** in which
processes run. After the processes are in the right order, the WT/TAT code is the same.

## 3. FCFS - First-Come, First-Served (Q1)

- Processes run in the order they were entered. No sorting.
- Non-preemptive: a running process is never interrupted.
- Problem: the **convoy effect**. One long process makes all short ones wait.

Worked example (classwork): P1 = 24, P2 = 3, P3 = 3

| Process | BT | WT | TAT |
| --- | --- | --- | --- |
| P1 | 24 | 0 | 24 |
| P2 | 3 | 24 | 27 |
| P3 | 3 | 27 | 30 |

Average WT = (0 + 24 + 27) / 3 = **17.00**, Average TAT = (24 + 27 + 30) / 3 = **27.00**

## 4. SJF - Shortest Job First (Q2)

- Sort processes by burst time, then run them in that order.
- `pid[]` is swapped along with `bt[]` so each burst stays with its process.
- SJF gives the **minimum average waiting time** when all processes arrive together.
- Problem: real burst times are not known in advance, and long jobs can starve.

Same input as FCFS, SJF order is P2, P3, P1:

| Process | BT | WT | TAT |
| --- | --- | --- | --- |
| P2 | 3 | 0 | 3 |
| P3 | 3 | 3 | 6 |
| P1 | 24 | 6 | 30 |

Average WT = **3.00**, Average TAT = **13.00**. Waiting time drops from 17 to 3.

## 5. Priority Scheduling (Q3)

- Sort by priority. Here a **smaller number means higher priority**.
- `priority[]`, `bt[]`, and `pid[]` are all swapped together.
- Problem: **starvation**. A low-priority process may wait forever.
- Fix: **aging**, which slowly raises the priority of a process the longer it waits.

Example: P1 (BT 10, Pr 3), P2 (1, 1), P3 (2, 4), P4 (1, 5), P5 (5, 2)

Order: P2, P5, P1, P3, P4. Average WT = **8.20**, Average TAT = **12.00**

## 6. Page replacement terms

- A **page** is a fixed-size block of a process's memory; a **frame** is a slot
  in RAM that holds one page.
- **Page hit:** the needed page is already in a frame.
- **Page fault:** the page is not in any frame, so it must be loaded. If all
  frames are full, one page is replaced.
- In the programs, `-1` marks an empty frame and is printed as `-`.

## 7. FIFO Page Replacement (Q4)

- Replace the page that was **loaded earliest**.
- `pointer` always points at the oldest frame. After a fault, it moves to the
  next frame: `pointer = (pointer + 1) % f;`
- A hit does **not** change `pointer`. FIFO only cares about load order, not use.
- **Belady's anomaly:** with FIFO, adding more frames can sometimes cause *more* faults.

## 8. LRU - Least Recently Used (Q5)

- Replace the page that has **not been used for the longest time**.
- `time` increases on every reference. `lastUsed[j]` stores when frame `j` was last used.
- On a hit, update `lastUsed`. On a fault, use an empty frame if available,
  otherwise replace the frame with the smallest `lastUsed`.
- LRU does not suffer from Belady's anomaly.

Worked example: reference string `7 0 1 2 0 3 0 4 2 3 0 3 2` with 3 frames

| Algorithm | Page faults |
| --- | --- |
| FIFO | 10 |
| LRU | 9 |

LRU keeps page `0` because it was used recently, while FIFO removes it
because it was loaded early.

## 9. How to compile and run the programs

```sh
cd "Week 7/Classwork"
gcc -std=c11 -Wall -Wextra Q1_fcfs.c -o q1
./q1
```

Change the file and executable name for each question. Arrays hold up to 20
processes or frames and up to 100 page references.

## 10. Quick viva revision

- **Which algorithm gives minimum average waiting time?** SJF (when all arrive together).
- **What is the convoy effect?** Short processes waiting behind a long one in FCFS.
- **What is starvation and how is it fixed?** A process waiting forever. Aging fixes it.
- **Preemptive vs non-preemptive?** Preemptive can interrupt a running process; non-preemptive lets it finish its burst.
- **Formula for TAT and WT?** `TAT = CT - AT`, `WT = TAT - BT`.
- **What is a page fault?** The requested page is not in memory.
- **What is Belady's anomaly?** More frames giving more page faults. It can happen in FIFO.
- **Why is LRU usually better than FIFO?** Recently used pages are likely to be used again (locality of reference).
- **What is the optimal page replacement algorithm?** Replace the page that will not be used for the longest time in the future. It cannot be implemented in practice and is used for comparison.

## 11. Questions covered

| Question | File | Topic |
| --- | --- | --- |
| Q1 | `Q1_fcfs.c` | FCFS CPU scheduling |
| Q2 | `Q2_sjf.c` | SJF CPU scheduling |
| Q3 | `Q3_priority.c` | Priority scheduling |
| Q4 | `Q4_fifo_page.c` | FIFO page replacement |
| Q5 | `Q5_lru_page.c` | LRU page replacement |

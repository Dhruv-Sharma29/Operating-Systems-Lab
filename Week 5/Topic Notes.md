# Week 5 - Topic Notes

## 1. Topics for this week

- Inter-Process Communication (IPC) using Named Pipes (FIFO).
- Creating a named pipe with `mkfifo()`.
- Unrelated process communication using file descriptors.
- Running separate reader and writer processes from different terminals.
- Blocking behavior of FIFO operations.

## 2. What is a Named Pipe (FIFO)?

A **FIFO** (First-In, First-Out), also called a **named pipe**, is an extension to the traditional pipe mechanism in Unix.
While an anonymous pipe (`pipe()`) only exists in memory and can only connect related processes (like parent and child sharing file descriptors after `fork()`), a **named pipe has a presence in the file system**.

- Any processes on the same system can communicate through a FIFO as long as they have access permissions to its path.
- The processes do not need to be parent and child.
- Although it appears as a file in the file system (with file type `p` in `ls -l`), data does not get stored on the disk drive; the operating system passes bytes through an internal kernel buffer.

## 3. Difference between Pipe and Named Pipe (FIFO)

| Feature | Ordinary / Anonymous Pipe (`pipe()`) | Named Pipe / FIFO (`mkfifo()`) |
| --- | --- | --- |
| **Creation** | `pipe(int pipefd[2])` system call | `mkfifo(const char *pathname, mode_t mode)` |
| **File System Presence** | None (exists only in memory / kernel buffer) | Exists as a special FIFO file in the file system |
| **Processes Involved** | Related processes only (parent and child via `fork()`) | Any unrelated processes with file permissions |
| **Lifespan** | Closes when all descriptors are closed | Persists in the file system until explicitly removed (`unlink()` or `rm`) |
| **Access Method** | Inherited file descriptors (`pipefd[0]`, `pipefd[1]`) | Standard file system calls (`open()`, `read()`, `write()`, `close()`) |

## 4. Key system calls and workflow

### `mkfifo()`
```c
int mkfifo(const char *pathname, mode_t mode);
```
- `pathname`: Path or name of the FIFO file (e.g., `"myfifo"`).
- `mode`: File permission bits (e.g., `0666` for read and write permission for all users, subject to umask).
- Returns `0` on success, or `-1` on error (e.g., if the FIFO already exists, `errno` is set to `EEXIST`).

### `open()`
```c
int fd = open("myfifo", O_WRONLY); // Writer process
int fd = open("myfifo", O_RDONLY); // Reader process
```
- Standard file opening using `<fcntl.h>`.
- **Important:** By default, opening a FIFO is a **blocking operation**:
  - Opening for read-only (`O_RDONLY`) blocks until some process opens the FIFO for writing.
  - Opening for write-only (`O_WRONLY`) blocks until some process opens the FIFO for reading.

### `write()` and `read()`
- The writer sends bytes into the FIFO:
  ```c
  write(fd, message, strlen(message) + 1);
  ```
- The reader consumes bytes from the FIFO:
  ```c
  read(fd, message, sizeof(message));
  ```

### `close()`
- Closes the process's file descriptor for the FIFO:
  ```c
  close(fd);
  ```

## 5. How to compile and run the programs

Because reader and writer are separate programs, run them in **two separate terminal windows**:

### Terminal 1 (Writer):
```sh
cd "Week 5/Classwork"
gcc -std=c11 -Wall -Wextra Q1_fifo_writer.c -o writer
./writer
```
The writer creates `"myfifo"`, prompts for a message, and waits for a reader to connect.

### Terminal 2 (Reader):
```sh
cd "Week 5/Classwork"
gcc -std=c11 -Wall -Wextra Q1_fifo_reader.c -o reader
./reader
```
The reader connects to `"myfifo"`, reads the message sent by the writer, prints it to the screen, and exits.

## 6. Quick viva revision

- **What does FIFO stand for?** First-In, First-Out.
- **Can unrelated processes communicate using ordinary pipes?** No, ordinary pipes require a common ancestor (via `fork()`). FIFOs allow unrelated processes to communicate.
- **Does a FIFO store data on disk?** No. Even though it has a directory entry in the filesystem, data is transferred through a kernel buffer in memory.
- **What happens if a process opens a FIFO for reading when no writer is present?** By default, the `open()` call blocks until a writer opens the FIFO.
- **How is a FIFO deleted from the file system?** Using the `unlink()` system call or the shell command `rm <fifo_name>`.
- **What file type indicates a FIFO in `ls -l`?** The letter `p` at the beginning of the permissions string (e.g., `prw-r--r--`).

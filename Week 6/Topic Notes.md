# Week 6 - Topic Notes

## 1. Topics for this week

- Inter-Process Communication (IPC) using System V Shared Memory.
- Inter-Process Communication (IPC) using System V Message Queues.
- Generating a common IPC key with `ftok()`.
- Running sender/writer and receiver/reader as separate programs.
- Inspecting and removing IPC resources with `ipcs` and `ipcrm`.

## 2. The IPC key: `ftok()`

```c
key_t key = ftok(".", 'S');
```

- `ftok()` turns a file path and a one-character project ID into a key.
- Both programs must use the **same path and the same character**, otherwise
  they get different keys and cannot find each other's resource.
- `"."` means the current directory, so run both programs from the same folder.
- Q1 (shared memory) uses `'S'`; Q2 (message queue) uses `'A'`.

## 3. Shared Memory (Q1)

Shared memory gives two processes **the same block of memory**. The writer
puts data in it, and the reader reads it directly from there. No `write()` or
`read()` call is needed to pass the data.

| Function | Purpose |
| --- | --- |
| `shmget(key, size, flags)` | Create or access a segment; returns its ID |
| `shmat(shmid, NULL, 0)` | Attach the segment; returns a pointer to it |
| `shmdt(pointer)` | Detach the segment from this process |
| `shmctl(shmid, IPC_RMID, NULL)` | Remove the segment from the system |

Order in Q1:

1. Writer: `ftok()` -> `shmget()` with `IPC_CREAT` -> `shmat()` -> `fgets()` straight into the shared memory -> `shmdt()`.
2. Reader: `ftok()` -> `shmget()` without `IPC_CREAT` -> `shmat()` -> `printf()` -> `shmdt()` -> `shmctl(IPC_RMID)`.

- `shmdt()` only detaches. The data stays in the segment after the writer exits,
  which is why the reader can run later.
- The reader uses `shmget()` **without** `IPC_CREAT`, so it fails with an error
  if the writer has not created the segment yet.
- **Run the writer first.** Shared memory has no built-in synchronization. If the
  reader runs first, it either finds nothing or reads before the writer finishes.
  Semaphores are used to coordinate this in real programs.

## 4. Message Queue (Q2)

A message queue is a list of messages kept by the kernel. The sender adds a
message; the receiver takes it out.

```c
struct message {
    long type;      // must be greater than 0
    char text[100]; // the data
};
```

| Function | Purpose |
| --- | --- |
| `msgget(key, flags)` | Create or access a queue; returns its ID |
| `msgsnd(msgid, &msg, size, 0)` | Add a message to the queue |
| `msgrcv(msgid, &msg, size, type, 0)` | Take a message of the given type |
| `msgctl(msgid, IPC_RMID, NULL)` | Remove the queue |

- The `size` passed to `msgsnd()` and `msgrcv()` is the size of the **text only**,
  not including `long type`.
- `msgrcv(..., 1, 0)` receives only messages of type `1`. Type `0` means "the
  first message of any type".
- The message waits in the queue until it is received, so the sender can run
  and exit before the receiver starts.
- If the receiver runs first, `msgrcv()` waits (blocks) until a message arrives.

## 5. FIFO vs Message Queue vs Shared Memory

| Feature | FIFO (Week 5) | Message Queue | Shared Memory |
| --- | --- | --- | --- |
| Data form | Stream of bytes | Separate messages with a type | A common memory block |
| Identified by | File path (`myfifo`) | IPC key / queue ID | IPC key / segment ID |
| Data access | `read()` / `write()` | `msgsnd()` / `msgrcv()` | Normal pointer access |
| Waits for the other side | `open()` blocks | `msgrcv()` blocks | No, you must sync yourself |
| Speed | Kernel copies data | Kernel copies data | Fastest, no copy |
| Removed by | `unlink()` | `msgctl(IPC_RMID)` | `shmctl(IPC_RMID)` |

## 6. How to compile and run the programs

### Q1 - Shared Memory

```sh
cd "Week 6/Classwork"
gcc -std=c11 -Wall -Wextra Q1_shm_writer.c -o writer
gcc -std=c11 -Wall -Wextra Q1_shm_reader.c -o reader
./writer      # Enter data: Shared Memory Example
./reader      # Data received: Shared Memory Example
```

### Q2 - Message Queue

```sh
cd "Week 6/Classwork"
gcc -std=c11 -Wall -Wextra Q2_msg_sender.c -o sender
gcc -std=c11 -Wall -Wextra Q2_msg_receiver.c -o receiver
./sender      # Enter message: Welcome to OS Lab
./receiver    # Received: Welcome to OS Lab
```

You can also run them in two terminals. Start `./receiver` first to see it
wait for the message.

### Inspecting IPC resources

```sh
ipcs -m          # list shared memory segments
ipcs -q          # list message queues
ipcrm -m <id>    # remove a shared memory segment
ipcrm -q <id>    # remove a message queue
```

Run `ipcs` after the writer/sender and again after the reader/receiver. The
resource disappears once the reader/receiver removes it.

## 7. Quick viva revision

- **Why do both programs call `ftok()` with the same arguments?** To get the same key, so they access the same segment or queue.
- **What does `shmat()` return?** A pointer to the shared memory inside the calling process.
- **Does `shmdt()` delete the shared memory?** No. It only detaches it. `shmctl(IPC_RMID)` removes it.
- **Why is shared memory the fastest IPC?** Data is not copied through the kernel. Both processes access the same memory.
- **Does shared memory provide synchronization?** No. Semaphores or similar tools are needed.
- **What is the `type` field in a message used for?** The receiver can choose which messages to receive.
- **Is `long type` counted in the size passed to `msgsnd()`?** No, only the text part.
- **How is a message queue different from a FIFO?** A queue keeps message boundaries and types; a FIFO is a plain byte stream.
- **Which command lists message queues and shared memory?** `ipcs -q` and `ipcs -m`.

## 8. Questions covered

| Question | Files | Topic |
| --- | --- | --- |
| Q1 | `Q1_shm_writer.c`, `Q1_shm_reader.c` | Shared memory |
| Q2 | `Q2_msg_sender.c`, `Q2_msg_receiver.c` | Message queue |

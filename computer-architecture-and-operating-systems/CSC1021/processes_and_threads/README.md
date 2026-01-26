# ***Peocesses & Threads***

***Process*** a program in execution. Process execution progresses in sequential feshion (i.e. no parallel execution of instructions of a single process).

### ***Memory Layout of a Program***

![virtual-memory-layout](./img/vm.jpg)

### ***Process State***
- ***New***: The process is being created
- ***Running***: Instructions are being executed
- ***Waiiting***: The process is waiting for some event to occure
- ***Ready***: The process is waiting to be assigned to a processor
- ***Terminated***: The process has finished execution

![process-states](./img/ps.jpg)


### ***Process Control Block (PCB)***
Information associated with each process (process state, program counter, cpu registers, cpu scheduling information, memory management information, I/O status information, etc.).


### ***Process Scheduling***
Process scheduler selects among available processes for next execution on CPU core. Also, it maintains scheduling queues of processes.
- ***Ready queue*** - set of all processes residing in main memory, ready and waiting to execute.
- ***Wait queues*** - set of processes waiting for an event e.g., I/O.


### ***Context Switch***
When CPU switches to another process, the system must save the state of the old process and load the saved state for the new process. The ***Context*** of a process represented in the ***PCB***.


Everything starts from ***systemd*** process (run `pstree`).

### ***Process Creation***

- `fork()` system call to create a new process by duplicating the current one.
- `exec()` replaces the current process image with a new program (loads a new program into that same process), (`execl()`, `execp()`, `execv()`, `execvp()`).
- `wait()` parent waits for child to finish.


### ***Process Termination***

Process executes last statement and then terminates by calling `exit()`. Exit status is recorded by the kernel and retrieved later by the parent via `wait()`. Process' resources are deallocated by OS.
Parent may terminate the execution of children process by sending a signal via `kill()`.

- ***orphan process*** - a child whose parent terminates before it finishes.
- ***zombie process*** - a child process that has finished execution but whose parent has NOT called `wait()` yet.

### ***Interprocess Communication***

Processes within a system may be independent or cooperating.
Cooperating processes can affect or be affected by other processes and even share data.

Cooperating processes need ***inter process communication*** (IPC)

![communication-models](./img/cm.jpg)



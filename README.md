ForkShell

A Unix-like command-line shell built in C using POSIX system calls. ForkShell demonstrates core Operating System concepts including process creation, command execution, inter-process communication, file descriptor manipulation, job management, and shell internals.

## Features

### Command Execution

Execute standard Linux commands.

```bash
myshell> ls
myshell> pwd
myshell> mkdir test
```

### Built-in Commands

```bash
cd
pwd
history
jobs
exit
```

### Background Processes

Run commands in the background.

```bash
myshell> sleep 10 &
[Background PID: 12345]
```

### Input Redirection

```bash
myshell> sort < input.txt
```

### Output Redirection

```bash
myshell> ls > output.txt
```

### Pipes

```bash
myshell> ls | grep txt

myshell> cat file.txt | sort
```

### Command History

```bash
myshell> history
```

### Job Management

```bash
myshell> jobs
```

---

## Project Structure

```text
ForkShell/
│
├── README.md
├── LICENSE
├── Makefile
│
├── src/
│   ├── main.c
│   ├── shell.c
│   ├── parser.c
│   ├── executor.c
│   ├── builtins.c
│   ├── background.c
│   ├── redirection.c
│   ├── pipes.c
│   ├── history.c
│   └── jobs.c
│
├── include/
│   ├── shell.h
│   ├── parser.h
│   ├── executor.h
│   ├── builtins.h
│   ├── background.h
│   ├── redirection.h
│   ├── pipes.h
│   ├── history.h
│   └── jobs.h
│
├── tests/
├── docs/
└── examples/
```

---

## Technologies Used

* C Programming Language
* Linux
* POSIX System Calls
* GCC
* Make
* Git & GitHub

---

## System Calls Used

| System Call | Purpose                     |
| ----------- | --------------------------- |
| fork()      | Create child process        |
| execvp()    | Execute external commands   |
| waitpid()   | Process synchronization     |
| pipe()      | Inter-process communication |
| dup2()      | Input/Output redirection    |
| open()      | Open files                  |
| close()     | Close files                 |
| chdir()     | Change directory            |
| getcwd()    | Print current directory     |

---

## Build

Using Makefile:

```bash
make
```

Or manually:

```bash
gcc src/*.c -Iinclude -o forkshell
```

---

## Run

```bash
./forkshell
```

---

## Example Session

```text
myshell> pwd
/home/anup

myshell> sleep 10 &
[Background PID: 12345]

myshell> jobs
[1] Running PID=12345 sleep

myshell> ls | grep txt
notes.txt

myshell> history

myshell> exit
```

---

## Learning Outcomes

* Operating System Fundamentals
* Process Creation & Management
* Linux System Programming
* Shell Design
* Inter-Process Communication (IPC)
* File Descriptor Manipulation
* Job Control
* Command Parsing

---

## Future Improvements

* Multiple Pipe Support
* fg / bg Commands
* Persistent History
* Environment Variables
* Auto Completion
* GUI Terminal Frontend
* POSIX Compliance Improvements

---

## Author

**Anup**

Built to explore Linux internals, process management, shell implementation, and systems programming using C.

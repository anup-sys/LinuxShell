# Linux Shell in C

A lightweight Unix/Linux shell built in C using POSIX system calls. This project demonstrates core Operating System concepts such as process creation, command execution, process synchronization, and shell internals.

## Features

* Execute Linux commands
* Built-in commands:

  * `cd`
  * `pwd`
  * `exit`
* Command parsing and tokenization
* Process creation using `fork()`
* Program execution using `execvp()`
* Parent-child synchronization using `waitpid()`
* Modular and extensible design

## Technologies Used

* C Programming Language
* Linux
* POSIX System Calls
* GCC
* Git & GitHub

## System Calls Used

### fork()

Creates a child process from the parent process.

### execvp()

Executes external Linux commands.

### waitpid()

Waits for child process completion.

### chdir()

Changes the current working directory.

### getcwd()

Retrieves the current working directory.

## Build

```bash
gcc src/*.c -Iinclude -o myshell
```

## Run

```bash
./myshell
```

## Usage

```bash
myshell> pwd
/home/user

myshell> mkdir test

myshell> ls

myshell> cd test

myshell> pwd
/home/user/test

myshell> exit
```

## Learning Outcomes

* Operating System Fundamentals
* Process Management
* Linux System Calls
* Command Execution
* Shell Architecture
* Parent-Child Process Communication

## Future Improvements

* Background Process Support (`&`)
* Input/Output Redirection (`<`, `>`)
* Pipes (`|`)
* Command History
* Job Control
* Multi-Pipe Execution
* Auto Completion

## Author

Anup

Built to explore Linux internals, system programming, and shell implementation using C.

# ForkShell Architecture

## Overview

ForkShell is a Unix-like command line shell implemented in C. It supports command execution, built-in commands, background processes, input/output redirection, pipes, command history, and job management.

The shell follows a modular architecture where each component is responsible for a specific task.

---

## High Level Architecture

```text
+-------------+
|   User      |
+------+------+ 
       |
       v
+-------------+
|  shell.c    |
|  main loop  |
+------+------+ 
       |
       v
+-------------+
|  parser.c   |
+------+------+ 
       |
       v
+----------------------+
| Builtin Dispatcher   |
| builtins.c           |
+----+-----------------+
     |
     +----------------------------+
     |                            |
     v                            v
Built-in Commands          External Commands
(cd, pwd, exit,            executor.c
 history, jobs)

                                 |
                                 v
                         +---------------+
                         | background.c  |
                         +---------------+

                                 |
                                 v
                         +---------------+
                         | redirection.c |
                         +---------------+

                                 |
                                 v
                         +---------------+
                         | pipes.c       |
                         +---------------+

                                 |
                                 v
                         fork() / execvp()
                                 |
                                 v
                         Linux Processes
```

---

## Module Responsibilities

### main.c

Entry point of the application.

Responsibilities:

* Start the shell
* Initialize components
* Call run_shell()

---

### shell.c

Main shell loop.

Responsibilities:

* Read user input
* Display prompt
* Store command history
* Parse commands
* Dispatch built-in commands
* Execute external commands

---

### parser.c

Command parsing module.

Responsibilities:

* Tokenize input
* Split command into arguments
* Prepare argument array for execvp()

Example:

Input:

```text
ls -l
```

Output:

```text
args[0] = ls
args[1] = -l
args[2] = NULL
```

---

### builtins.c

Handles built-in shell commands.

Supported Commands:

* cd
* pwd
* exit
* history
* jobs

These commands execute inside the shell process and do not require fork().

---

### executor.c

Executes external programs.

Responsibilities:

* fork()
* execvp()
* waitpid()

Execution Flow:

```text
Parent
   |
 fork()
   |
+--+--+
|     |
v     v
Child Parent
 |      |
execvp() waitpid()
```

---

### background.c

Handles background execution.

Example:

```text
sleep 10 &
```

Responsibilities:

* Detect '&'
* Remove '&' from argument list
* Skip waitpid()
* Support concurrent execution

---

### redirection.c

Handles input and output redirection.

Supported:

```text
ls > output.txt
sort < input.txt
```

System Calls:

* open()
* dup2()
* close()

---

### pipes.c

Handles process communication using pipes.

Supported:

```text
ls | grep txt
cat file.txt | sort
```

System Calls:

* pipe()
* fork()
* dup2()

---

### history.c

Maintains command history.

Responsibilities:

* Store executed commands
* Display command history

Command:

```text
history
```

---

### jobs.c

Tracks background processes.

Responsibilities:

* Add jobs
* List jobs
* Remove completed jobs

Commands:

```text
jobs
fg
bg
```

---

## System Calls Used

| System Call | Purpose                     |
| ----------- | --------------------------- |
| fork()      | Create child process        |
| execvp()    | Execute program             |
| waitpid()   | Wait for child process      |
| pipe()      | Inter-process communication |
| dup2()      | Redirection                 |
| open()      | Open file                   |
| close()     | Close file                  |
| chdir()     | Change directory            |
| getcwd()    | Get current directory       |

---

## Directory Structure

```text
ForkShell/
├── src/
├── include/
├── tests/
├── docs/
└── examples/
```

---

## Future Improvements

* Multiple Pipes
* Persistent History
* Job Control (fg/bg)
* Environment Variables
* Auto Completion
* GUI Terminal Frontend
* POSIX Compliance Improvements

---

## Conclusion

ForkShell demonstrates core operating system concepts including process creation, process management, inter-process communication, file descriptor manipulation, and command interpretation.

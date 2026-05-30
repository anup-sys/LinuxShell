# System Calls Used in ForkShell

## Overview

ForkShell relies on several Linux system calls to implement process creation, command execution, input/output redirection, pipes, and job control.

This document explains the purpose and usage of each system call used in the project.

---

# 1. fork()

## Purpose

Creates a new child process.

## Prototype

```c
pid_t fork(void);
```

## Return Value

| Return Value | Meaning                       |
| ------------ | ----------------------------- |
| 0            | Child Process                 |
| > 0          | Parent Process (PID of child) |
| -1           | Error                         |

## Example

```c
pid_t pid = fork();

if (pid == 0)
{
    printf("Child Process\n");
}
else
{
    printf("Parent Process\n");
}
```

## Usage in ForkShell

Used in:

* executor.c
* pipes.c

Creates a child process to execute commands.

---

# 2. execvp()

## Purpose

Replaces the current process image with a new program.

## Prototype

```c
int execvp(const char *file, char *const argv[]);
```

## Example

```c
char *args[] = {"ls", "-l", NULL};

execvp(args[0], args);
```

## Usage in ForkShell

Used after fork() to execute external commands.

Example:

```text
myshell> ls
myshell> grep main.c
```

---

# 3. waitpid()

## Purpose

Waits for a child process to finish.

## Prototype

```c
pid_t waitpid(pid_t pid, int *status, int options);
```

## Example

```c
waitpid(pid, NULL, 0);
```

## Usage in ForkShell

Foreground processes:

```text
myshell> ls
```

Parent waits until child exits.

Background processes:

```text
myshell> sleep 10 &
```

Parent does not wait.

---

# 4. pipe()

## Purpose

Creates a communication channel between processes.

## Prototype

```c
int pipe(int fd[2]);
```

## Returned File Descriptors

```text
fd[0] -> Read End
fd[1] -> Write End
```

## Example

```c
int fd[2];

pipe(fd);
```

## Usage in ForkShell

Used to implement:

```text
ls | grep txt
cat file.txt | sort
```

---

# 5. dup2()

## Purpose

Duplicates file descriptors.

## Prototype

```c
int dup2(int oldfd, int newfd);
```

## Example

```c
dup2(fd, STDOUT_FILENO);
```

## Usage in ForkShell

Output Redirection:

```text
ls > output.txt
```

Input Redirection:

```text
sort < input.txt
```

Pipe Redirection:

```text
ls | grep txt
```

---

# 6. open()

## Purpose

Opens a file.

## Prototype

```c
int open(const char *pathname,
         int flags,
         mode_t mode);
```

## Example

```c
open("output.txt",
     O_WRONLY | O_CREAT | O_TRUNC,
     0644);
```

## Usage in ForkShell

Output Redirection:

```text
ls > output.txt
```

Input Redirection:

```text
sort < input.txt
```

---

# 7. close()

## Purpose

Closes an open file descriptor.

## Prototype

```c
int close(int fd);
```

## Example

```c
close(fd);
```

## Usage in ForkShell

Used after:

* open()
* pipe()
* dup2()

Prevents file descriptor leaks.

---

# 8. chdir()

## Purpose

Changes the current working directory.

## Prototype

```c
int chdir(const char *path);
```

## Example

```c
chdir("Documents");
```

## Usage in ForkShell

Built-in command:

```text
cd Documents
```

Implemented in:

```text
builtins.c
```

---

# 9. getcwd()

## Purpose

Returns current working directory.

## Prototype

```c
char *getcwd(char *buf, size_t size);
```

## Example

```c
char cwd[1024];

getcwd(cwd, sizeof(cwd));
```

## Usage in ForkShell

Built-in command:

```text
pwd
```

---

# 10. kill()

## Purpose

Sends signals to processes.

## Prototype

```c
int kill(pid_t pid, int sig);
```

## Example

```c
kill(pid, SIGCONT);
```

## Usage in ForkShell

Future support:

```text
fg
bg
```

Signals:

```text
SIGSTOP
SIGCONT
SIGTERM
```

---

# Standard File Descriptors

Linux provides three standard file descriptors.

| Descriptor | Name          |
| ---------- | ------------- |
| 0          | STDIN_FILENO  |
| 1          | STDOUT_FILENO |
| 2          | STDERR_FILENO |

Examples:

```text
Keyboard -> STDIN
Terminal -> STDOUT
Error Messages -> STDERR
```

---

# Process Execution Flow

```text
User Command
      |
      v
Parser
      |
      v
fork()
      |
      +----------------+
      |                |
      v                v
Parent            Child
(waitpid)       execvp()
      |                |
      +----------------+
               |
               v
        External Program
```

---

# Redirection Flow

```text
ls > output.txt

STDOUT
   |
 dup2()
   |
output.txt
```

---

# Pipe Flow

```text
ls | grep txt

Process 1 (ls)
      |
      v
    PIPE
      |
      v
Process 2 (grep txt)
```

---

# Conclusion

ForkShell demonstrates practical usage of Linux system calls related to process management, inter-process communication, file descriptor manipulation, and command execution. These system calls form the foundation of modern Unix-like operating systems and shell environments.

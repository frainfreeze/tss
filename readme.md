# tss - Tom's Simple Shell
A shell or command-line interpreter is a user interface for access to an operating system's 
services. In general, operating system shells use either a command-line interface (CLI) 
or graphical user interface (GUI), depending on a computer's role and particular 
operation. It is named a shell because it is the outermost layer around the operating 
system kernel.

> Although most users think of the shell as an interactive command interpreter, it is really a programming language in which each statement runs a command. Because it must satisfy both the interactive and programming aspects of command execution, it is a strange language, shaped as much by history as by design. — Brian Kernighan & Rob Pike

## Shell in a nutshell
In it's essence shell is a Read–Eval–Print Loop (REPL), a simple, interactive computer 
programming environment that takes single user inputs (i.e. single expressions), evaluates 
them, and returns the result to the user.

Typical shell workflow is as follows:
- Startup: read and execute configuration files
- Wait for user input and interpret (read commands from stdin (interactive/file) and execute them)
    - Parsing
    - Expansion
    - Execution
- Terminate: executes any shutdown commands, free up any memory, and terminate

## Startup
`Compare the output of echo $HOME in your shell to your regular shell. Your regular shell treats tokens beginning with $ specially: it looks them up by name in the environment, and substitutes them in the command. The `getenv` function looks up a variable in the environment. This can be handled during or after parsing a command.`


## System calls
The way our programs talk to the kernel is through system calls. 
These are operations we can tell the kernel to do on our behalf. 
Examples include:
    - opening files (`open`)
    - reading and writing to them (`read`, `write`)
    - sending and receiving data over the network. (`sendto`, `recvfrom`)
    - starting programs (`execve`)
    - process creating a copy of itself (`fork`)

In fact, more or less everything that involves our programs interacting 
with the ‘real world’ involves system calls.

Shell is parent process so it utilizes system call `fork`, this helps us
to isolate commands which is important for fault tolerance. We dont want
erroneous command to crash whole shell. The `fork` creates a new process 
that is a clone of the existing one, right down to the point in the program 
that's executing. We can then call exec in the newly created child process, 
leaving our shell's process around for future interaction.

The return value of fork tells us if we're in the child or the parent: 
it returns 0 for the child, and the id of the new process in the parent.

To wait for the child process to finish we can use `wait` system call.

## Builtins
Every process has its own its own memory and extra metadata that the kernel 
manages, but that the process can't change directly. Process can use system
calls to change user id (`setuid`), group id (`setgid`), priority (`setpriority`), 
working directory (`chdir`).

If you were to call change directory command it would invoke `chdir` internally,
change its working dir and return to the parent process - however parents process
working dir would stay unchanged, therefore shell has to have builting `cd` command
that calls `chdir` system call on shell process itself. The handling of cd is then 
built in to our shell — it's a builtin.

In bash, `export` lets us change an environment variable's value in the shell itself. 
As with `cd`, because a child cannot modify its parent's environment, export must be 
a builtin.

See manpages on bash builtins [man builtins](https://linux.die.net/man/1/builtins) for more.

## Pipeline
In Unix-like computer operating systems, a pipeline is a sequence of processes 
chained together by their standard streams, so that the output of each process 
(stdout) feeds directly as input (stdin) to the next one. 

Pipes are unidirectional; data flows through the pipeline from left to right.

```
process1 | process2 | process3
```

The `pipe()` system call asks the operating system to construct a new anonymous 
pipe object. This results in two new, opened file descriptors in the process: 
the read-only end of the pipe, and the write-only end. The pipe ends appear to 
be normal, anonymous file descriptors, except that they have no ability to seek.

To avoid deadlock and exploit parallelism, the Unix process with one or more new 
pipes will then, generally, call `fork()` to create new processes. Each process 
will then close the end(s) of the pipe that it will not be using before producing 
or consuming any data. Alternatively, a process might create a new thread and use 
the pipe to communicate between them.

Named pipes may also be created using `mkfifo()` or `mknod()` and then presented 
as the input or output file to programs as they are invoked. They allow multi-path 
pipes to be created, and are especially effective when combined with standard error 
redirection, or with tee. 

In most Unix-like systems, all processes of a pipeline are started at the same time, 
with their streams appropriately connected, and managed by the scheduler together with 
all other processes running on the machine. An important aspect of this, setting Unix 
pipes apart from other pipe implementations, is the concept of buffering: for example 
a sending program may produce 5000 bytes per second, and a receiving program may only 
be able to accept 100 bytes per second, but no data is lost. Instead, the output of the 
sending program is held in the buffer. When the receiving program is ready to read data, 
then next program in the pipeline reads from the buffer. In Linux, the size of the buffer 
is 65536 bytes (64KiB).

https://github.com/kamalmarhubi/shell-workshop#6-pipelines
+ IO redirection to/from files: https://github.com/kamalmarhubi/shell-workshop#2-io-redirection-tofrom-files


## Terminate
`Compare what happens when you hit ^C (control-C) between your shell and your regular shell. ^C 
sends a signal to your process, in this case `SIGINT`. Signals interrupt the normal execution of 
your program. By default, this aborts the process. To prevent that, we can register a signal 
handler function to be called when `SIGINT` is received, or decide to ignore it.`


## Todo:
### Globbing
Compare the output of wc -c * between your shell and your regular shell. Expanding the wildcard * 
is done by the shell before passing arguments to the child. The glob function in the <glob.h> 
standard header will be useful.

### Running a command in the background
In your regular shell, if you end a command with &, it runs in the background. The command will 
run, but the shell will not block while it does. Ie, it does not wait on the child process.

## Refs:
- https://en.wikipedia.org/wiki/Shell_(computing)
- https://en.wikipedia.org/wiki/Bourne_shell
- https://linux.die.net/man/1/bash
- http://man7.org/linux/man-pages/dir_section_3.html
- https://en.wikipedia.org/wiki/Pipeline_(Unix)
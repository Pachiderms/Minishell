# Minishell - As beautiful as a shell
This project has been created as part of the 42 curriculum by [Your Name/Login] and [Partner Name/Login].

## Description
Minishell is a 42 project that consists of creating a simple command-line interpreter, essentially our own version of Bash. This project is a deep dive into the inner workings of a computer, focusing on process management, file descriptors, and signal handling.

The goal is to provide an interactive interface that can execute commands, handle complex redirections, and manage environment variables while maintaining a clean execution cycle (Prompt -> Lexer -> Parser -> Executor).

## Key Features
- Interactive Prompt: Displays a prompt and maintains a working command history.
- Command Execution: Searches and launches executables based on the PATH variable or absolute/relative paths.
- Built-ins: Implementation of ```echo (-n)```, ```cd```, ```pwd```, ```export```, ```unset```, ```env```, and ```exit```.
- Redirections: ```<``` (input), ```>``` (output), ```>>``` (append).
- << (here-doc) with delimiter handling.
- Pipes: ```|``` connects the output of one command to the input of the next.
- Environment Variables: Expansion of $VAR and $? (exit status).
- Signal Handling: Proper behavior for ```ctrl-C```, ```ctrl-D```, and ```ctrl-\```.
- Quoting: Handles ```'``` (literal) and ```"``` (expansion) appropriately.

## Technical Challenges
- The Pipe Pipeline: Implementing a recursive or iterative execution of pipes while correctly closing all file descriptors to avoid "hanging" processes.
- Signal Integrity: Ensuring that ctrl-C in a child process (like cat) behaves differently than in the main prompt.
- Memory Management: Tracking every allocated string during expansion and parsing to ensure no leaks (excluding known readline leaks).

## Instructions
### Compilation
The project uses a standard Makefile. To compile the program, run:
```bash
make
```
## Launch the shell using:
```bash
./minishell
```
### Usage
You can use it just like a standard shell:
```bash
minishell> ls -la | grep "txt" > output.txt
minishell> cat << EOF
```

## Resources
- https://harm-smits.github.io/42docs/projects/minishell
- ```man``` for every built-in behaviour

# SIMPLE SHELL PROJECT
## 0x16. project is a simple UNIX command interpreter done by Solomon Musyoki and Cynthia Odoyo
### The Shell Should:
1. Display a prompt and wait for the user to type a command. A command line always ends with a new line.
2. Handle command lines with arguments.
3. Handle the PATH.
4. Implement the exit built-in, that exits the shell.
5. Implement the env built-in, that prints the current environment.
6. Write your own getline function.
7. Handle arguments for the built-in exit.
8. Implement the setenv and unsetenv builtin commands.
9. Implement the builtin command cd:
10. Handle the commands separator ;
11. Handle the && and || shell logical operators.
12. Implement the alias builtin command.
13. Handle variables replacement /$? variable and /$$ variable.
14. Handle comments (#).
15. The shell can take a file as a command line argument.

## Functions and system calls
### List of allowed functions and system calls

* access (man 2 access)
* chdir (man 2 chdir)
* close (man 2 close)
* closedir (man 3 closedir)
* execve (man 2 execve)
* exit (man 3 exit)
* _exit (man 2 _exit)
* fflush (man 3 fflush)
* fork (man 2 fork)
* free (man 3 free)
* getcwd (man 3 getcwd)
* getline (man 3 getline)
* getpid (man 2 getpid)
* isatty (man 3 isatty)
* kill (man 2 kill)
* malloc (man 3 malloc)
* open (man 2 open)
* opendir (man 3 opendir)
* perror (man 3 perror)
* read (man 2 read)
* readdir (man 3 readdir)
* signal (man 2 signal)
* stat (__xstat) (man 2 stat)
* lstat (__lxstat) (man 2 lstat)
* fstat (__fxstat) (man 2 fstat)
* strtok (man 3 strtok)
* wait (man 2 wait)
* waitpid (man 2 waitpid)
* wait3 (man 2 wait3)
* wait4 (man 2 wait4)
* write (man 2 write)


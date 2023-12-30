**C - Simple Shell Group Project**
**Team: Zeynal Mustafayev, Mahammadsaleh Abbas**

**Requirements**
Allowed editors: vi, vim, emacs

All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89

All your files should end with a new line

A README.md file, at the root of the folder of the project is mandatory

Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl

Your shell should not have any memory leaks

No more than 5 functions per file

All your header files should be include guarded

Use system calls only when you need to

**Tasks**
 UNIX command line interpreter.

Usage: simple_shell

Your Shell should:

Display a prompt and wait for the user to type a command. A command line always ends with a new line.
The prompt is displayed again each time a command has been executed.
The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
The command lines are made only of one word. No arguments will be passed to programs.
If an executable cannot be found, print an error message and display the prompt again.
Handle errors.
You have to handle the “end of file” condition (Ctrl+D)
Handle command lines with arguments
Handle the PATH
Implement the exit built-in, that exits the shell
Usage: exit
Handle arguments for the built-in exit
Usage: exit status, where status is an integer used to exit the shell
Handle Ctrl+C: your shell should not quit when the user inputs ^C
Implement the env built-in, that prints the current environment
Implement the setenv and unsetenv builtin commands
setenv
Initialize a new environment variable, or modify an existing one
Command syntax: setenv VARIABLE VALUE
Should print something on stderr on failure
unsetenv
Remove an environment variable
Command syntax: unsetenv VARIABLE
Should print something on stderr on failure
Implement the builtin command cd:
Changes the current directory of the process.
Command syntax: cd [DIRECTORY]
If no argument is given to cd the command must be interpreted like cd $HOME
You have to handle the command cd -
You have to update the environment variable PWD when you change directory
Handle the commands separator ;
Handle the && and || shell logical operators
Implement the alias builtin command
Usage: alias [name[='value'] ...]
alias: Prints a list of all aliases, one per line, in the form name='value'
alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'
alias name='value' [...]:
Defines an alias for each name whose value is given. If name is already an alias, replaces its value with value
Handle variables replacement
Handle the $? variable
Handle the $$ variable
Handle comments (#)
Implement the help built-in
Usage: help [BUILTIN]
Implement the history built-in, without any argument
The history built-in displays the history list, one command by line, preceded with line numbers (starting at 0)
On exit, write the entire history, without line numbers, to a file named .simple_shell_history in the directory $HOME
When the shell starts, read the file .simple_shell_history in the directory $HOME if it exists, and set the first line number to the total number of lines in the file modulo 4096
Usage: simple_shell [filename]
Your shell can take a file as a command line argument
The file contains all the commands that your shell should run before exiting
The file should contain one command per line
In this mode, the shell should not print a prompt and should not read from stdin

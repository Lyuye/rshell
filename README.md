#Rshell

Lyuye Niu 861244218

CS100 - Homework 1
Writing a Basic Command Shell

This shell is able to perform the following steps:
Commands will have the form:
```
cmd         = executable [ argumentList ] [ connector cmd ]
connector   = || or && or ;
```
where `executable` is an executable program in the `PATH` and `argumentList` is a list of zero or more arguments separated by spaces.
The connector is an optional way you can run multiple commands at once.
If a command is followed by `;`, then the next command is always executed;
if a command is followed by `&&`, then the next command is executed only if the first one succeeds;
if a command is followed by `||`, then the next command is executed only if the first one fails.
For example:
```
$ ls -a
$ echo hello
$ mkdir test
```
is equivalent to:
```
$ ls -a; echo hello; mkdir test
```
To run this shell, follw this steps

clone my repository
$ cd rshell
$ git checkout hw1
$ make
$ bin/shell


The code has bugs as follow

1. "echo a || echo b ; echo c" returns only "a"
   "false || echo b ; echo c" returns "b /n c"
   So "||" covered all of commands behind, except for using "false ||"
2. "false && echo a" returns "a" instead of "Null"
 


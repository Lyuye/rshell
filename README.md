#Rshell

Lyuye Niu 861244218

CS100 - Homework 2
The Test Command and Precedence Operators

Your subset of the test command should allow the user to run the command using the keyword "test"
Additionally, you will implement parentheses ( ) as precedence operators in your rshell. The
parentheses ( ) operators are used to change the precedence of the returns of commands,
connectors, and chains of connectors.

Design:
Use "stat()" to do "test". And use the S_ISDIR and S_ISREG to implement "-e" "-f" "-d".
Now this code achieved run test "-e" "-f" "-d" with connectors "||" "&&" ";".
In future I should think more hard to do precedence operators.

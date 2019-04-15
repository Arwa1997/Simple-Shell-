# Simple-Shell-
A simple shell program that takes commands from the keyboard and gives them to the operating system to perform.

There are 3 main parts to thise code: 
1. Reading & Parsing 

To read the line the function "readLine" uses "fgets" and the parameter "stdin" was entered to scan a full string from the console. The string where the line was saved in is then sent to another function called "removeEnter" which basically removes the "\n" that is added to the end of each string after the user presses enter, and replaces it with the null character to terminate the string as to aid in the parsing process.
The parsing function is called by the main and it takes an array of pointers (which will point to the split tokens (arguments) of the entered string when its finished) and the string entered. It also returns an int, which is the size of the current array of arguments if it is not empty.

2. Execution

Execution mainly takes place in the main. There are different types of commands. "cd" and "exit" were handled seperately. To execute the "cd" command, the "chdir" function was called before forking. While the function "exit(0)" was called whenever an "exit" command was entered. The rest of the commands were handled automatically by the " execvp" function, where the first argument was passed, as well as the whole array of arguments. 
Another function was added "isBackground" to check for the presence of "&" at the end of the functions that want to run in the background. Here is where the size of the array of arguments comes in handy, as we can check for the last element in the array directly. This function returns an int which is later used as a flag to determine if the parent should wait for the child to terminate or not
The main is in a while loop that only terminates when the command "exit" is entered.
 

3. Signal Handling

The last part of the code is the signal handler. After inserting the signal library, a function signal which takes the parameters SIGCHLD (a built in flag that gets triggered when the child process is terminated) and another function called "signalhandler" that was added to write into a log file whenever a child process gets terminated.



 


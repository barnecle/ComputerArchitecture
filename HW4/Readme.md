#Explaination of sys_info

The program reads one command line argument that is a Linux command which includes either the path of the command (/bin/) or not. First the program will send errors or exit if too few or too many args are given. Then the program creates a pipe and then a child process through the fork() function. 
The Parent process prints its P.I.D. and then writes the command line argument into the write end of the pipe. After closing the write end, the parent function waits for the child function to complete.
The child process prints out its own P.I.D. and that of its parent. Then it reads from the read end of the pipe and formats the command line arg into either a command name or a path. The name and path are entered as arguments into the execl function and then executed if the command is a valid command. If not, the errno value will be less than 0, and an error message will pop up before the function exits. 

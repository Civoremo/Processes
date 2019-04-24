// Write a program that calls `fork()`. Before calling `fork()`, have the main process access a variable
// (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process?
// What happens to the variable when both the child and parent change the value of x?

// 1. variable value in child process remains the same value as the initial value
// 2. changing value dirung child process will change value on exit / same for parent

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    // Your code here
    int x = 100;
    
    printf("X value before fork: %d, (pid: %d) \n", x, getpid());

    int our_fork = fork();

    if (our_fork < 0)
    {
        // fork failed
        fprintf(stderr, "Fork Failed!\n");
    } else if  (our_fork == 0)
    {
        // fork successful
        x = 150;
        printf("Child here (pid: %d), (X: %d) \n", (int) getpid(), x);
    } else 
    {
        // x = 125;
        printf("Parent here (pid: %d), (X: %d) \n", (int) getpid(), x);
    }

    printf("X value after fork: %d, (pid: %d) \n", x, getpid());

    return 0;
}

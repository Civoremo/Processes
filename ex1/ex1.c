// Write a program that calls `fork()`. Before calling `fork()`, have the main process access a variable
// (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process?
// What happens to the variable when both the child and parent change the value of x?

// 1. variable value in child process remains the same value as the initial value
// 2. changing value during child process will change value of child process value on exit / same for parent

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
        exit(1);
    } else if  (our_fork == 0)
    {
        // fork successful
        printf("Child here (pid: %d), (X: %d) \n", (int) getpid(), x);
        x = 150;
        printf("Child, X value is now: %d \n", x);
    } else 
    {
        int wc = waitpid(our_fork, NULL, 0);
        printf("Parent here (pid: %d), (X: %d) \n", (int) getpid(), x);
        x = 125;
        printf("Parent, X value is now: %d \n", x);
    }

    printf("X value after fork: %d, (pid: %d) \n", x, getpid());

    return 0;
}

// Write a program that calls `fork()` and then calls some form of `exec()`
// to run the program `/bin/ls`. Try a few variants of `exec()`, such as 
// `execl()`, `execle()`, `execv()`, and others. Why do you think there 
// are so many variants of the same basic call?

// 1. that is a very good question; it appears that all perform the same task but with slight difference in syntax

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
    // Your code here    
    int our_fork = fork();

    if (our_fork < 0) {
        fprintf(stderr, "Fork Failed!\n");
    } else if (our_fork == 0) {
        printf("CHILD!\n");
        
        // char *myargs[] = {"ls", "-1", NULL};
        char *myargs[] = {"../ex3/ex3", "-1", NULL};

        // execvp("ls", myargs);

        // execl("/bin/ls", "ls", "-1", (char *) NULL);

        // execv("/bin/ls", myargs);
        execv(myargs[0], myargs);

        // execlp("ls", "ls", "-1", (char *) NULL);
    } else {
        int wc = waitpid(our_fork, NULL, 0);
        printf("PARENT!\n");
    }

    return 0;
}

// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write 
// the three messages to the parent and have the parent print out 
// the messages. 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MSGSIZE 16

char* msg1 = "hello world #1";
char* msg2 = "hello world #2";
char* msg3 = "hello world #3";

int main(void)
{
    // Your code here
    char inbuf[MSGSIZE];
    int p[2];

    if (pipe(p) < 0) {
        fprintf(stderr, "Pipe Failed!\n");
        exit(1);
    }

    // write(p[1], msg1, MSGSIZE);
    // write(p[1], msg2, MSGSIZE);
    // write(p[1], msg3, MSGSIZE);

    // for (int i = 0; i < 3; i++) {
    //     read(p[0], inbuf, MSGSIZE);
    //     printf("%s \n", inbuf);
    // }


    int our_fork = fork();

    if (our_fork < 0) {
        fprintf(stderr, "Failed Fork!\n");
        exit(2);
    } else if (our_fork == 0) {
        printf("CHILD!\n");

        write(p[1], msg1, MSGSIZE);
        write(p[1], msg2, MSGSIZE);
        write(p[1], msg3, MSGSIZE);

    } else {
        int wc = waitpid(our_fork, NULL, 0);
        close(p[1]);
        printf("PARENT!\n");

        for (int i = 0; i < 3; i++) {
            read(p[0], inbuf, MSGSIZE);
            printf("%s \n", inbuf);
        }
    }
    
    return 0;
}

// Write another program using `fork()`. The child process should print "hello";
// the parent process should print "goodbye". You should ensure that the child
// process always prints first.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    // Your code here
    int our_fork = fork();

    if (our_fork < 0) {
        // fork failed
        fprintf(stderr, "Fork Failed!\n");
    } else if (our_fork == 0) {
        char *kid = "hello, ";
        printf("%s", kid);
    } else {
        int wc = waitpid(our_fork, NULL, 0);
        char *adult = "goodbye";
        printf("%s", adult);
    }

    return 0;
}

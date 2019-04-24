// Write a program that opens the text.txt file (with the `fopen()` library call) located in this directory 
// and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor 
// returned by `fopen()`? What happens when they are written to the file concurrently?

// 1. both the child and parent can access fopen
// 2. both add text to file; order is determined by which one executes first

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(void)
{
    // Your code here 
    FILE *our_file = fopen("text.txt", "w");

    int our_fork = fork();
    char *someText = "Hello World, Welcome to C! ";
    char *childish = "KIDS \n";
    char *grown = "PARENT \n";

    if (our_fork < 0) {
        // fork failed
        fprintf(stderr, "Fork Failed! \n");
        exit(1);
    } else if (our_fork == 0) {
        // Child Successful
        char *our_child = "CHILD TEXT\n";

        printf("Child fork %p \n", our_file);

        fwrite(someText, sizeof(char), strlen(someText), our_file);
        fwrite(childish, sizeof(char), strlen(childish), our_file);
        fwrite(our_child, sizeof(char), strlen(our_child), our_file);
        fputs("Child Testing Direct String Write to File\n\n", our_file);
        // puts("Child here again!");  // writes the string s and a trailing newline to stdout.
        // fclose(our_file);  // function flushes the stream pointed to by stream and closes the underlying file descriptor.
        
        printf("Child finished writing\n");

    } else {
        // Parent
        char *our_parent = "PARENT TEXT\n";
        int wc = waitpid(our_fork, NULL, 0);

        printf("Parent again %p \n", our_file);

        fwrite(someText, sizeof(char), strlen(someText), our_file);
        fwrite(our_parent, sizeof(char), strlen(our_parent), our_file);

        printf("Parent finished writing\n");
    }

    printf("AFTER FORK: %p \n", our_file);
    
    return 0;
}

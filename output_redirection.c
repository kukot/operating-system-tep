#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // the child process
        // now we will redirect the output of the wc program into a file instead of the standard output

        // first, close the std output
        close(STDOUT_FILENO);

        // now open a new file
        open("./redirection_output.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

        // now exec the wc
        char *myargs[3];
        myargs[0] = strdup("wc"); // the wc program
        myargs[1] = strdup("output_redirection.c"); // the file to count
        myargs[2] = NULL; // mark the end of array
        execvp(myargs[0], myargs); // run word count with the arguments above
    } else {
        // parent process will go down this path
        int rc_wait = wait(NULL);
    }
    return 0;
}


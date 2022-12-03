#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc, char * argv[]) {
    printf("Hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {// child (new process)
        printf("Hello, I am child (pid:%d)\n", (int) getpid());

        // prepare to run word count
        char *myargs[3];
        myargs[0] = strdup("wc"); // the program wc - word count
        myargs[1] = strdup("exec_simple.c"); // a parameter pass to the wc program, which is the file name
        myargs[2] = NULL; // the NULL marks the end of an array
        execvp(myargs[0], myargs);
        printf("This shouldn't print out");
    } else {
        int rc_wait = wait(NULL);
        printf("Hello, I am parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
    }
    printf("Hi, finally");
    return 0;
}

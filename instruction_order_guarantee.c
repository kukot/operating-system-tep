#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc > 0) {
        // parent process goes here
        wait(NULL);
        printf("Goodbye\n");
    } else if (rc == 0) {
        // child process goes here
        printf("Hello\n");
    } else {
        // rc < 0, fork failed
        fprintf(stderr, "Fork failed, exit\n");
        exit(1);
    }

    return 0;
}
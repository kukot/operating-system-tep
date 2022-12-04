#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) { // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // the child process
        // first, close the std output
        close(STDOUT_FILENO);
        printf("Hello, this little kid is trying to print out something after closing stdout\n");
    } else {
        // parent process will go down this path
        int rc_wait = wait(NULL);
        printf("Hello, I am the parent\n");
    }
    return 0;
}
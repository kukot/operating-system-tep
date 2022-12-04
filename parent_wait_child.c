#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rc = fork();

    if (rc > 0) {
        // parent process
        int rc_wait = wait(NULL);
        printf("Hello, I am parent (pid:%d)\n", (int) getpid());
        printf("Wait return value = %d\n", rc_wait);
    } else if (rc == 0) {
        // child goes here
        printf("Hello, I am child (pid:%d)\n", (int) getpid());
    } else {
        // fork failed
        fprintf(stderr, "fork failed, exit");
        exit(1);
    }
}
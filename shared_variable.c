#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int shared_variable = 100;
    int rc = fork();
    if (rc > 0) {
        // parent process goes here
        int rc_wait = wait(NULL);
        printf("Hello, I am parent process (pid: %d)\n", (int) getpid());
        printf("PID: %d: shared_variable: %d\n", (int) getpid(), shared_variable);
    } else if (rc == 0) {
        // child process goes here
        int childId = (int) getpid();
        printf("Hello, I am child process (pid: %d)\n", childId);
        printf("PID: %d: shared_variable: %d\n", childId, shared_variable);
        printf("PID: %d: Changing the variable value to 500\n", childId);
        shared_variable = 500;
        printf("PID: %d: shared_variable: %d\n", childId, shared_variable);
    } else {
        // rc < 0, fork failed
        fprintf(stderr, "fork failed, exit");
        exit(1);
    }

    return 0;
}
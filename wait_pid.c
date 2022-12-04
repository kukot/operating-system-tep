#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    int child_status = 10;

    if (rc == 0) {
        // child goes here
        printf("Hello, I am child (pid:%d)\n", (int) getpid());
        exit(EXIT_SUCCESS);
    } else if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed, exit");
        exit(1);
    }
    // int rc_wait = waitpid(rc, &child_status, WNOHANG | WCONTINUED | WUNTRACED);
    printf("Hello, I am parent (pid:%d)\n", (int) getpid());
    int rc_wait = waitpid(rc, &child_status, 0);
    printf("Waitpid return value = %d\n", rc_wait);
    printf("child_status: %d\n", child_status);

    if (WIFSIGNALED(child_status)) {
        printf("Error in child process!\n");
    } else if (WEXITSTATUS(child_status)) {
        printf("Child exited normally");
    }
    return 0;
}
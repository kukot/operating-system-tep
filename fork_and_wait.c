#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("Hello world (pid: %d)\n", (int) getpid());
    int rc = fork();
    if (rc <0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("Hello, I am child (pid:%d)\n", (int) getpid());
        int rcc = fork();
        if (rcc > 0) {
            wait(NULL);
            printf("Hello, I've just given birth to the grandchild (pid:%d)\n", (int) rcc);
        } else if (rcc == 0) {
            printf("Hi, I am the mentioned grandchild, my name is (pid %d)\n", (int) getpid());
        }
    } else {
        // parent goes down this path (main)
        wait(NULL);
        printf("Hello, I am parent of %d (pid:%d) \n", rc, (int) getpid());
    }
    printf("Hi, finally");
    return 0;
}

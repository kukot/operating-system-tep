#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MSG_SIZE 16

char *msg1 = "hello, world #1";
char *msg2 = "hello, world #2";

int main(int argc, char *argv[]) {
    // for simplicity, we will be assuming that the two children are created successfully
    int parent_pid = (int) getpid();
    printf("Parent (PID: %d)\n", parent_pid);
    int shared_pipes[2];
    pipe(shared_pipes); // initialize pipe, one in idx[0] will be the read, idx[1] will be the write
    int elder_brother;
    int younger_brother;
    char inbuff[MSG_SIZE];
    elder_brother = fork();
    // TODO: find out why the very next line is printed twice
    if (elder_brother > 0) {
        int wait_elder = wait(NULL); // intentionally wait for elder brother to finish writing to the pipe
        printf("PID: %d just finished\n", wait_elder);
        // parent goes here
        younger_brother = fork();
        if (younger_brother >0) {
            // parent goes inside this again
        } else if (younger_brother == 0) {
            // younger brother read
            close(shared_pipes[1]);
            read(shared_pipes[0], inbuff, MSG_SIZE);
            printf("Younger brother (PID: %d) : read from the pipe: %s\n", (int) getpid(), inbuff);
        }
    } else if (elder_brother == 0) {
        // elder brother write to pipe
        close(shared_pipes[0]);
        write(shared_pipes[1], msg1, MSG_SIZE);
        printf("Elder brother (PID: %d): wrote to pipe\n", (int) getpid());
    }
    return 0;
}
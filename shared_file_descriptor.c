#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

    int file_descriptor = open("./shared_file.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    int rc = fork();
    if (rc > 0) {
        // parent process goes here
        write(file_descriptor, "parent wrote here\n", strlen("parent wrote here\n"));
        write(file_descriptor, "2nd line parent wrote here\n", strlen("2nd line parent wrote here\n"));
        wait(NULL); // wait for the child to finish their job before writing the last line of text
        write(file_descriptor, "3rd line parent wrote here\n", strlen("3rd line parent wrote here\n"));
    } else if (rc == 0) {
        // child process
        write(file_descriptor, "Child doing some stuff\n", strlen("Child doing some stuff\n"));
        write(file_descriptor, "2nd line child doing some stuff\n", strlen("2nd line child doing some stuff\n"));
        write(file_descriptor, "3rd line child doing some stuff\n", strlen("3rd line child doing some stuff\n"));
        close(file_descriptor);
    } else {
        // fork failed, exit
        fprintf(stderr, "Fork failed, exit");
        exit(1);
    }
    return 0;
}
#include <stdio.h>
#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc > 0) {
        // parent process goes here
        wait(NULL);
        printf("Parent printing out\n");
    } else if (rc == 0) {
        // child process goes here, prepare to run the /bin/ls program
        char *path_to_ls = strdup("/bin/ls");// this is used when using the non-*p version
        char *ls = strdup("ls");
        char *list_all = strdup("-la");
        char *termination = NULL;

        char *vector_args[] = {ls, list_all, termination}; // vector style, using with the v* version
        // execl(path_to_ls, ls, list_all, termination); // list of argument, using full-path to the file to be executed
        // execle(path_to_ls, path_to_ls, list_all, termination);
        // execlp(ls, ls, list_all, termination);
        // execlp(path_to_ls, ls, list_all, termination);// the *p version can accept the full path as well
        // execv(path_to_ls, vector_args);
        execvp(ls, vector_args);
        // execvpe(ls, vector_args);
        printf("This shouldn't print out\n");
    } else {
        // fork returned -1, failed
        fprintf(stderr, "fork failed, exit");
        exit(1);
    }

    return 0;
}